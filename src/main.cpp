#include "mainwindow.h"
#include"welcomepage.h"

#include"NewProjectWizard/secondpage.h"
#include"NewProjectWizard/firstpage.h"

#include"media/videoinformation.h"
#include<subtittleProcess/dividestr2dict.h>
#include <QApplication>
#include<QFileDialog>
#include<iostream>
#include<QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);

//    QString fileName = QFileDialog::getOpenFileName();
//    VideoInformation* v1 = new VideoInformation();
//        v1->getVideoInfo(fileName);

//        qDebug()<<fileName;
//        qDebug()<<"duration: "<<v1->getDuration();
//        qDebug()<< "format: "<<v1->getFormat();
//        qDebug()<< "video frame rate: "<<v1->getFrameRate();
//        qDebug()<<"video bit rate: "<<v1->getVideoAverageBitRate();
//        qDebug()<<"video format: "<<v1->getVideoFormat();
//        qDebug()<< "video width: "<<v1->getWidth();
//        qDebug()<< "video height: "<<v1->getHeight();
//        qDebug()<< "video size: "<<v1->getVideoSize();
//        qDebug()<<  "audio bit rate: "<<v1->getAudioAverageBitRate();
//        qDebug()<< "audio format: "<<v1->getAudioFormat();
//        qDebug()<< "audio size: "<<v1->getAudioSize();
//        qDebug()<< "audio smaple rate: "<<v1->getSampleRate();
//        qDebug()<<"audio channel numbers: "<<v1->getChannelNumbers();

    /*DivideStr2dict dic;
    dic.get_word_frequency("I:\\learnEnglishWithFilms\\bin\\Im.Thinking.of.Ending.Things.2020.1080p\\test.str");*/

    WelcomePage w;
    w.show();
    return a.exec();
}
