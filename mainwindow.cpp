#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "menu.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectButton_clicked()
{
    this->filePath = QFileDialog::getOpenFileName(this, tr("select file"), " ",  tr("Allfile(*.*);;"));
    this->ui->filePath->setText(this->filePath);
}

void MainWindow::on_downloadButton_clicked()
{
    this->fileName = this->ui->fileName->text();

    //QString to char*
    QByteArray ba = this->fileName.toLocal8Bit();
    char* c_str2 = ba.data();

    menu Menu = menu();
    Menu.selectedFunction = 2; //download
    Menu.showMenu();

    int retVal = Menu.download(c_str2);
    if(retVal == -1) {
        this->ui->messageLabel->setText("Server does not exist this file");
    } else if(retVal == -2) {
        this->ui->messageLabel->setText("create file fail");
    } else if(retVal == 0) {
        this->ui->messageLabel->setText("Success");
        //---
        //解密
        //文件名删除enc
        //删除加密的文件
        //---
    }
    return;
}

void MainWindow::on_uploadButton_clicked()
{
    QByteArray ba = this->filePath.toLocal8Bit();
    char* c_str2 = ba.data();

    menu Menu = menu();
    Menu.selectedFunction = 1;  //upload
    Menu.showMenu();

    int retVal = Menu.upload(c_str2);

    switch (retVal) {
    case 0:
        this->ui->messageLabel->setText("Success");
        break;
    case -1:
        this->ui->messageLabel->setText("Local file not exist");
        break;
    case -2:
        this->ui->messageLabel->setText("Server-side error");
        break;
    case -3:
        this->ui->messageLabel->setText("Hash read error");
        break;
    case -4:
        this->ui->messageLabel->setText("Hash exist");
        break;
    case -5:
        this->ui->messageLabel->setText("Can not open hashFile");
        break;
    }

    //---
    //删除加密的文件
    //---
    return;
}











