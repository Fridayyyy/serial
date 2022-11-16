//
// Created by Administrator on 2022/11/14.
//

#ifndef SERIAL_SERIAL_H
#define SERIAL_SERIAL_H
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QPushButton>
#include <QTextBrowser>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

#include "videoPlayer.h"


class serial :public QMainWindow{
    Q_OBJECT
public:
    serial(QWidget *parent= nullptr);

private:
    videoPlayer player;

    QSerialPort *serialPort;

    QTextBrowser *textBrowser;

    QTextEdit *textEdit;

    QPushButton *pushButton[2];

    QComboBox *comboBox[5];

    QLabel *label[5];

    QVBoxLayout *vboxLayout;

    QGridLayout *gridLayout;

    QWidget *mainWidget;

    QWidget *funcWidget;

    void layoutInit();

    void scanSerialPort();

    void baudRateItemInit();

    void dataBitsItemInit();


    void parityItemInit();


    void stopBitsItemInit();

private slots:
    void sendPushButtonClicked();
    void openSerialPortPushButtonClicked();
    void serialPortReadyRead();


};


#endif //SERIAL_SERIAL_H
