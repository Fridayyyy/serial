#include <QApplication>
#include <QPushButton>
#include "videoPlayer.h"
#include "serial.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    videoPlayer v;
//    v.show();
    serial serial;
    serial.show();

    return QApplication::exec();
}
