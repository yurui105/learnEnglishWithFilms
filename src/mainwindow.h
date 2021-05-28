#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QJsonDocument>
#include<QJsonObject>
#include"subtittleProcess/dividestr2dict.h"
#include<QMessageBox>
#include<QVector>
#include<qprogressbar.h>
#include"videocutthread.h"
#include<QtOpenGLWidgets/qopenglwidget.h>
#include"QMDKWidget.h"
#include <QWidget>
#include <memory>
#include <QFileDialog>
#include "QDebug"
#include <QThread>
#include <QMouseEvent>
#include <QStyle>
#include <QTimer>
#include<regex>

namespace mdk {
class Player;
}


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_project_config(QJsonDocument config){project_config=config;}
    void set_project_status(bool status);//设置项目是否为新项目

private:
    QJsonDocument project_config;
    Ui::MainWindow *ui;
    //字幕文件对象
    DivideStr2dict* subtitle;
    bool isNewProject;

    

public slots:
    void init_subtitle();
    void startThread_slot() { qDebug() << "准备睡眠"; _sleep(10000); qDebug() << "睡眠十秒执行"; }
    //视频处理线程相关
    void openThreadSlot();
    void closeThreadSlot();
    void process(int a);
    void on_word_table_click(int x,int y);

    //视频播放相关
    void timeout_update();//时间更新
    void on_pushButton_pause_clicked();//暂停
    void on_pushButton_reset_clicked();//重新播放
    void on_pushButton_play_clicked();//播放
    void on_pushButton_stop_clicked();//停止
//    void on_pushButton_Volume_clicked();//静音
    void loadMedia(QString filePath);
    void on_horizontalSlider_Volume_valueChanged(int value);
    //判断是否播放下一个视频

signals:
    void startThread_signal();
    void setMedia(QString filePath);

private:
    void setWordsTable();
    void analysis_subtitle();
    QVector<std::pair<QString, time_fre>> tvector;
    QString project_path;
    QString video_path;
    
    QVector<QString> play_time;

    //线程对象
    QThread* firstThread;
    VideoCutThread* cutThread;
    int current;

    //视频播放
    void on_btnOpen_clicked();
//    bool eventFilter(QObject *obj, QEvent *event);
    QTimer *timer;
    bool eventFilter(QObject *obj, QEvent *event);
    int64_t current_video_duration;
};
#endif // MAINWINDOW_H
