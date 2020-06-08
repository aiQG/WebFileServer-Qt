/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *messageLabel;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLineEdit *filePath;
    QPushButton *selectButton;
    QPushButton *uploadButton;
    QVBoxLayout *verticalLayout;
    QLineEdit *fileName;
    QPushButton *downloadButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(631, 202);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(31, 41, 521, 95));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        messageLabel = new QLabel(widget);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));

        verticalLayout_2->addWidget(messageLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        filePath = new QLineEdit(widget);
        filePath->setObjectName(QString::fromUtf8("filePath"));
        filePath->setEnabled(false);

        gridLayout->addWidget(filePath, 0, 0, 1, 2);

        selectButton = new QPushButton(widget);
        selectButton->setObjectName(QString::fromUtf8("selectButton"));

        gridLayout->addWidget(selectButton, 0, 2, 1, 1);

        uploadButton = new QPushButton(widget);
        uploadButton->setObjectName(QString::fromUtf8("uploadButton"));

        gridLayout->addWidget(uploadButton, 1, 0, 1, 3);


        horizontalLayout->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        fileName = new QLineEdit(widget);
        fileName->setObjectName(QString::fromUtf8("fileName"));
        fileName->setEnabled(true);

        verticalLayout->addWidget(fileName);

        downloadButton = new QPushButton(widget);
        downloadButton->setObjectName(QString::fromUtf8("downloadButton"));

        verticalLayout->addWidget(downloadButton);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 631, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        messageLabel->setText(QString());
        selectButton->setText(QCoreApplication::translate("MainWindow", "Select File", nullptr));
        uploadButton->setText(QCoreApplication::translate("MainWindow", "Upload", nullptr));
        downloadButton->setText(QCoreApplication::translate("MainWindow", "Download", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
