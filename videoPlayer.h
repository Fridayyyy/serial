//
// Created by Administrator on 2022/11/14.
//

#ifndef SERIAL_VIDEOPLAYER_H
#define SERIAL_VIDEOPLAYER_H
#include <QBoxLayout>
#include <QWidget>
#include <QtWidgets/QWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QFileDialog>
#include <QPushButton>
class videoPlayer: public QWidget{
    Q_OBJECT
public:
    videoPlayer(QWidget *parent=0);

private:
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QBoxLayout *layout;
    QPushButton *playButton;
    QPushButton *fileButton;

    void init();
public slots:
    void play();
    void onButtonSetClicked();
};


#endif //SERIAL_VIDEOPLAYER_H
