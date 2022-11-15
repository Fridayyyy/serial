//
// Created by Administrator on 2022/11/14.
//

#include "videoPlayer.h"
#include <string>

videoPlayer::videoPlayer(QWidget *parent) : QWidget(parent){
    init();

}

void videoPlayer::init() {
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

    mediaPlayer=new QMediaPlayer(this,QMediaPlayer::VideoSurface);

    videoWidget=new QVideoWidget;

    this->resize(QSize(1400,1800));

    //按钮，连接
    playButton=new QPushButton("play");
    fileButton=new QPushButton("file");
    connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(fileButton, SIGNAL(clicked(bool)), this, SLOT(onButtonSetClicked()));

    //布局
    layout=new QVBoxLayout;
    layout->addWidget(videoWidget);
    layout->addWidget(fileButton);
    layout->addWidget(playButton);

    mediaPlayer->setVideoOutput(videoWidget);

    setLayout(layout);

}

void videoPlayer::play() {
    mediaPlayer->play();
}

void videoPlayer::onButtonSetClicked() {
    QString fileName="D:\\qtProjects\\serial\\videos\\test.mp4";
    mediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(fileName)));

}
