#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QJsonDocument>
#include<QJsonObject>
#include"subtittleProcess/dividestr2dict.h"
#include<QMessageBox>
#include<QVector>
#include <QThread>
#include"videocutthread.h"

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

private:
    QJsonDocument project_config;
    Ui::MainWindow *ui;
    //字幕文件对象
    DivideStr2dict* subtitle;

    

public slots:
    void init_subtitle();
    void startThread_slot() { qDebug() << "准备睡眠"; _sleep(10000); qDebug() << "睡眠十秒执行"; }
    //视频处理线程相关
    void openThreadSlot();
    void closeThreadSlot();

signals:
    void startThread_signal();

private:
    void setWordsTable();
    void analysis_subtitle();
    QVector<pair<QString, time_fre>> tvector;
    QString project_path;
    QString video_path;

    //线程对象
    QThread* firstThread;
    VideoCutThread* cutThread;

    //视频播放
    void on_btnOpen_clicked();

};
#endif // MAINWINDOW_H
