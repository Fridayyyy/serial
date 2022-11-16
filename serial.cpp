//
// Created by Administrator on 2022/11/14.
//

#include "serial.h"
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <iostream>

serial::serial(QWidget *parent) : QMainWindow(parent){
    layoutInit();

    scanSerialPort();

    baudRateItemInit();


    dataBitsItemInit();


    parityItemInit();


    stopBitsItemInit();

}

void serial::layoutInit() {

    QList <QScreen *> list_screen = QGuiApplication::screens();
    this->resize(800, 480);

    serialPort = new QSerialPort(this);
    textBrowser = new QTextBrowser();
    textEdit = new QTextEdit();
    vboxLayout = new QVBoxLayout();
    funcWidget = new QWidget();
    mainWidget = new QWidget();
    gridLayout = new QGridLayout();


    QList <QString> list1;
    list1<<"串口号:"<<"波特率:"<<"数据位:"<<"检验位:"<<"停止位:";

    for (int i = 0; i < 5; i++) {
        label[i] = new QLabel(list1[i]);

        label[i]->setMinimumSize(80, 30);

        label[i]->setSizePolicy(
                QSizePolicy::Expanding,
                QSizePolicy::Expanding
        );

        gridLayout->addWidget(label[i], 0, i);

       }

    for (int i = 0; i < 5; i++) {
        comboBox[i] = new QComboBox();
        comboBox[i]->setMinimumSize(80, 30);

        comboBox[i]->setSizePolicy(
                QSizePolicy::Expanding,
                QSizePolicy::Expanding
        );

        gridLayout->addWidget(comboBox[i], 1, i);
        }


    QList <QString> list2;
    list2<<"发送"<<"打开串口";

    for (int i = 0; i < 2; i++) {
        pushButton[i] = new QPushButton(list2[i]);
        pushButton[i]->setMinimumSize(80, 30);

        pushButton[i]->setSizePolicy(
                QSizePolicy::Expanding,
                QSizePolicy::Expanding
        );

        gridLayout->addWidget(pushButton[i], i, 5);
        }
    pushButton[0]->setEnabled(false);


    vboxLayout->addWidget(textBrowser);
    vboxLayout->addWidget(textEdit);
    funcWidget->setLayout(gridLayout);
    vboxLayout->addWidget(funcWidget);
    mainWidget->setLayout(vboxLayout);
    this->setCentralWidget(mainWidget);


    textBrowser->setPlaceholderText("接收到的消息");
    textEdit->setText("www.openedv.com");


    connect(pushButton[0], SIGNAL(clicked()),
                this, SLOT(sendPushButtonClicked()));
    connect(pushButton[1], SIGNAL(clicked()),
                this, SLOT(openSerialPortPushButtonClicked()));
    connect(serialPort, SIGNAL(readyRead()),
                this, SLOT(serialPortReadyRead()));

}

void serial::scanSerialPort() {
    foreach (const QSerialPortInfo &info,
             QSerialPortInfo::availablePorts()) {
        comboBox[0]->addItem(info.portName());
    }
}
void serial::baudRateItemInit() {
    QList <QString> list;
    list<<"1200"<<"2400"<<"4800"<<"9600"
    <<"19200"<<"38400"<<"57600"
    <<"115200"<<"230400"<<"460800"
    <<"921600";
    for (int i = 0; i < 11; i++) {
        comboBox[1]->addItem(list[i]);
        }
    comboBox[1]->setCurrentIndex(7);

}

void serial::dataBitsItemInit() {
    QList <QString> list;
    list<<"5"<<"6"<<"7"<<"8";
    for (int i = 0; i < 4; i++) {
        comboBox[2]->addItem(list[i]);
        }
    comboBox[2]->setCurrentIndex(3);
}

void serial::parityItemInit() {
    QList <QString> list;
    list<<"None"<<"Even"<<"Odd"<<"Space"<<"Mark";
    for (int i = 0; i < 5; i++) {
        comboBox[3]->addItem(list[i]);
        }
    comboBox[3]->setCurrentIndex(0);

}
void serial::stopBitsItemInit() {
    QList <QString> list;
    list<<"1"<<"2";
    for (int i = 0; i < 2; i++) {
        comboBox[4]->addItem(list[i]);
        }
    comboBox[4]->setCurrentIndex(0);

}

void serial::sendPushButtonClicked() {
    QByteArray data = textEdit->toPlainText().toUtf8();
    serialPort->write(data);
}

void serial::openSerialPortPushButtonClicked() {
    if (pushButton[1]->text() == "打开串口") {

        serialPort->setPortName(comboBox[0]->currentText());

        serialPort->setBaudRate(comboBox[1]->currentText().toInt());

        switch (comboBox[2]->currentText().toInt()) {
            case 5:
                serialPort->setDataBits(QSerialPort::Data5);
                break;
            case 6:
                serialPort->setDataBits(QSerialPort::Data6);
                break;
            case 7:
                serialPort->setDataBits(QSerialPort::Data7);
                break;
            case 8:
                serialPort->setDataBits(QSerialPort::Data8);
                break;
            default:
                break;
        }
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        if (!serialPort->open(QIODevice::ReadWrite))
            QMessageBox::about(NULL, "错误","串口无法打开！可能串口已经被占用！");
        else {
            for (int i = 0; i < 5; i++)
                comboBox[i]->setEnabled(false);
            pushButton[1]->setText("关闭串口");
            pushButton[0]->setEnabled(true);
        }

    }else {
        serialPort->close();
        for (int i = 0; i < 5; i++)
            comboBox[i]->setEnabled(true);
        pushButton[1]->setText("打开串口");
        pushButton[0]->setEnabled(false);
    }

}
void serial::serialPortReadyRead() {
    std::cout<<"open"<<std::endl;

    player.show();
    player.onButtonSetClicked();
    player.play();

    QByteArray buf = serialPort->readAll();
    textBrowser->insertPlainText(QString(buf));
}