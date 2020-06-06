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
    if(retVal == -1) {
        this->ui->messageLabel->setText("file not exist");
    } else if(retVal == -2) {
        this->ui->messageLabel->setText("Server-side error");
    } else if(retVal == 0) {
        this->ui->messageLabel->setText("Success");
    }
    return;
}











