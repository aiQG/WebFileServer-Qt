#include "menu.h"

menu::menu()
{
    //初始化请求
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&this->serv_addr, 0, sizeof(this->serv_addr));     //每个字节都用0填充
    this->serv_addr.sin_family = AF_INET;                     //使用IPv4地址
    this->serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //具体的IP地址
    this->serv_addr.sin_port = htons(1234);                   //端口
    connect(this->sock, (struct sockaddr *)&this->serv_addr, sizeof(this->serv_addr));

    this->selectedFunction = 0;
}

menu::~menu()
{
    char buffer[BUFFER_SIZE] = {0};
    //文件读取完毕, 断开输出流, 发送FIN包
    shutdown(this->sock, SHUT_WR);
    //阻塞等待客户端返回ACK包
    recv(this->sock, buffer, BUFFER_SIZE, 0);
    close(this->sock);
}

void menu::showMenu()
{
    send(this->sock, &this->selectedFunction, 4, 0);
    return;
}

bool menu::catFile(char *filename)
{
    send(this->sock, filename, strlen(filename), 0);

    char buffer[BUFFER_SIZE] = {0};
    recv(this->sock, buffer, 1, 0);
    if (*buffer == 'N')
    {
        return false;
    }
    else
    {
        return true;
    }
}

int menu::download(char *filename)
{
    char filename_server[BUFFER_SIZE];
    memset(filename_server, 0, BUFFER_SIZE);
    strcpy(filename_server, filename);
    strcat(filename_server, ".enc");
    if (!catFile(filename_server))
    {
        std::cout << "Server does not exist this file"
                  << std::endl;
        return -1;
    }

    //创建本地文件
    FILE *fp = fopen(filename_server, "wb"); //二进制写(创建)
    if (fp == NULL)
    {
        printf("create file fail\n");
        return -2;
    }
    sleep(1); //防止粘包
    //循环接收数据, 直到传输完毕
    char buffer[BUFFER_SIZE] = {0};
    memset(buffer, 0, BUFFER_SIZE); //清空缓冲
    int nCount = 0;
    while ((nCount = recv(this->sock, buffer, BUFFER_SIZE, 0)) > 0)
    {
        fwrite(buffer, nCount, 1, fp);
    }
    fclose(fp);
    std::cout << "Download success" << std::endl;

    //解密
    fp = fopen(filename_server, "rb");
    unsigned char c_str2[BUFFER_SIZE];
    memset(c_str2, 0, BUFFER_SIZE);
    unsigned long fileSize = sizeof(c_str2);
    fread(c_str2, sizeof(c_str2), 1, fp);
    fclose(fp);
    unsigned char* decBuffer = (unsigned char*)malloc((fileSize / 16 + 1) * 16);
    memset(decBuffer, 0, (fileSize / 16 + 1) * 16);
    memcpy(decBuffer, c_str2, fileSize);
    uint8_t key[16] = {0}; // key == k*16
    memset(key, 'k', 16);
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    struct AES_ctx AESDecBlock;
    AES_init_ctx_iv(&AESDecBlock, key, iv);
    AES_CBC_decrypt_buffer(&AESDecBlock, decBuffer, (fileSize / 16 + 1) * 16);
    unsigned int ii = 0;
    while (decBuffer[ii] <= 0x7f) {
        ii++;
    }
    char temp[100] = "../../../";
    strcat(temp, filename);
    fp = fopen(temp, "wb"); //二进制写(创建)
    if (fp == NULL)
    {
        printf("create file fail\n");
        return -2;
    }
    fwrite(decBuffer, ii, 1, fp);
    fclose(fp);
    return 0;
}

int menu::upload(char *filename)
{
    char buffer[BUFFER_SIZE] = {0};
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        char x[] = "\xFF";
        send(this->sock, x, strlen(x), 0);
        std::cout << "Local file not exist" << std::endl;

        return -1;
    }
    fclose(fp);
    // 文件存在则加密
    QFile fphash(filename);
    if (!fphash.open(QIODevice::ReadOnly | QIODevice::Text))
            return -3;
    QTextStream in(&fphash);
    QString str = in.readAll();
    fphash.close();
    //QString to char*
    QByteArray ba = str.toLocal8Bit();
    char* c_str2 = ba.data(); //明文
    unsigned long fileSize = strlen(c_str2);
    unsigned char* encBuffer = (unsigned char*)malloc((fileSize / 16 + 1) * 16);
    memset(encBuffer, 0, (fileSize / 16 + 1) * 16);
    memcpy(encBuffer, c_str2, fileSize);
    uint8_t key[16] = {0}; // key == k*16
    memset(key, 'k', 16);
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    struct AES_ctx AESEncBlock;
    AES_init_ctx_iv(&AESEncBlock, key, iv);
    AES_CBC_encrypt_buffer(&AESEncBlock, encBuffer, (fileSize / 16 + 1) * 16);
/*
 * 解密
    struct AES_ctx AESDecBlock;
    AES_init_ctx_iv(&AESDecBlock, key, iv);
    AES_CBC_decrypt_buffer(&AESDecBlock, encBuffer, (fileSize / 16 + 1) * 16);
*/

    //提取出文件名
    char filename_srever[100] = {0};
    for(int i = 0, j = 0; i < (int)strlen(filename); i++) {
        if(filename[i] == '/') {
            memset(filename_srever, 0, 100);
            j = 0;
        } else {
            filename_srever[j] = filename[i];
            j++;
        }
    }

    strcat(filename_srever, ".enc");
    FILE* encFP = fopen(filename_srever, "w");
    fwrite(encBuffer, (fileSize / 16 + 1) * 16, 1, encFP);
    fclose(encFP);

    //---
    //加密
    //文件名加enc
    //---

    //计算hash
    QFile fphash2(filename_srever);
    if (!fphash2.open(QIODevice::ReadOnly | QIODevice::Text))
            return -3;
    QTextStream in2(&fphash2);
    QString str2 = in2.readAll();
    QString hash = QString("%1").arg(QString(QCryptographicHash::hash(str2.toUtf8(),QCryptographicHash::Sha1).toHex()));
    //QString to char*
    QByteArray sha1temp = hash.toLocal8Bit();
    char* sha1Code = sha1temp.data();
    //发送hash
    send(this->sock, sha1Code, strlen(sha1Code), 0);

    recv(this->sock, buffer, 1, 0);
    if (*buffer == 'H')
    {
        std::cout << "Hash exist" << std::endl;
        return -4;
    } else if (*buffer == 'N')
    {
        std::cout << "Can not open hashFile" << std::endl;
        return -5;
    }



    send(this->sock, filename_srever, strlen(filename_srever), 0); //发送文件名

    recv(this->sock, buffer, 1, 0);
    if (*buffer != 'Y')
    {
        std::cout << "Server-side error" << std::endl;
        return -2;
    }

    sleep(1); //防止粘包
    //循环发送数据, 直到传输完毕
    memset(buffer, 0, BUFFER_SIZE); //清空缓冲区
    int nCount = 0;
    fp = fopen(filename_srever, "rb");
    while ((nCount = fread(buffer, 1, BUFFER_SIZE, fp)) > 0)
    {
        send(this->sock, buffer, nCount, 0);
    }
    fclose(fp);
    // 清除本地加密文件
    char cmd[BUFFER_SIZE] =  "rm ";
    strcat(cmd, filename_srever);
    system(cmd);

    return 0;
}

int menu::deleteFile(char *filename)
{
    if (!catFile(filename))
    {
        std::cout << "Server does not exist this file"
                  << std::endl;
        return -1;
    }
    std::cout << "success" << std::endl;
    return 0;
}
