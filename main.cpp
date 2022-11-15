#include <QApplication>
#include <QPushButton>
#include "videoPlayer.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    videoPlayer v;
    v.show();

    return QApplication::exec();
}
