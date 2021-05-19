#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QStandardItemModel>
#include"welcomepage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QObject::connect(wizard,SIGNAL(let_main_window_init_subtitle()),this,SLOT(init_subtitle()),Qt::QueuedConnection);
    QObject::connect(this, &MainWindow::startThread_signal, this, &MainWindow::openThreadSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openThreadSlot()
{
    /*开启一条多线程*/
    qDebug() << tr("开启线程");
    firstThread = new QThread;                                                      //线程容器
    cutThread = new VideoCutThread;
    cutThread->set_time(subtitle->getOccurrencesTime());
    cutThread->setPath(project_path);
    cutThread->setVideoPath(video_path);
    cutThread->moveToThread(firstThread);                                      //将创建的对象移到线程容器中
    connect(firstThread, SIGNAL(finished()), cutThread, SLOT(deleteLater()));        //终止线程时要调用deleteLater槽函数
    connect(firstThread, SIGNAL(started()), cutThread, SLOT(startWoker()));  //开启线程槽函数
    connect(firstThread, SIGNAL(finished()), this, SLOT(finishedThreadSlot()));
    firstThread->start();
}

void MainWindow::closeThreadSlot()
{
    qDebug() << tr("关闭线程");
    if (firstThread->isRunning())
    {
        cutThread->closeThread();  //关闭线程槽函数
        firstThread->quit();            //退出事件循环
        firstThread->wait();            //释放线程槽函数资源
    }
}

void MainWindow::init_subtitle()
{
    //初始化字幕数据
    analysis_subtitle();
    //设置词频表
    setWordsTable();


    //新线程处理视频
    emit startThread_signal();


    //截图专用
    QImage* img = new QImage; //新建一个image对象

    img->load(":/icon/image/mulan.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
    QPixmap map = QPixmap::fromImage(*img);
    //int with = ui->label->width();
    //int height = ui->label->height();
    //QPixmap fitpixmap = map.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(map); //将图片放入label，使用setPixmap,注意指针*img
}

void MainWindow::setWordsTable()
{
    //设置词频表格
    QVector<pair<QString, time_fre>> words = subtitle->get_sorted_sequence();
    int i=0;
    for(auto it = words.begin();it!=words.end();it++){
        ui->words_table->insertRow(i);
        ui->words_table->setItem(i,0,new QTableWidgetItem(QString::number(i + 1)));
        ui->words_table->setItem(i,1,new QTableWidgetItem(it->first));
        ui->words_table->setItem(i,2,new QTableWidgetItem(QString::number(it->second.frequency)));
        i++;
    }

    //演示专用
    QVector<pair<QString, QString>> time = subtitle->getOccurrencesTime();
    i = 0;
    for (auto it = time.begin(); it != time.end(); it++) {
        ui->words_table_2->insertRow(i);
        ui->words_table_2->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1)));
        ui->words_table_2->setItem(i, 1, new QTableWidgetItem((it->first+"---"+it->second)));
        i++;
    }
}

void MainWindow::analysis_subtitle()
{
    QJsonObject config=project_config.object();

    //获取项目路径
    if (config.contains("ProjectPath")) {
        QJsonValue path = config.value("ProjectPath");
        if (path.isString()) {
            project_path = path.toString();
        }
    }
    //获取视频路径
    if (config.contains("VideoPath")) {
        QJsonValue path = config.value("VideoPath");
        if (path.isString()) {
            video_path = path.toString();
        }
    }


    //判断配置文件对象是否包含SubtittleInfo字段
    if(config.contains("SubtittleInfo")){

        //将SubtittleInfo字段取出
        QJsonValue subtitleInfo = config.value("SubtittleInfo");

        //判断SubtittleInfo是否是一个json对象
        if(subtitleInfo.isObject()){

            //如果是，将SubtittleInfo转换为对象
            QJsonObject value = subtitleInfo.toObject();

            //判断SubtittleInfo对象中是否包含Path字段
            if(value.contains("Path")){

                //取出Path字段
                QJsonValue pathValue= value.value("Path");

                //判断该字段是否有数据
                if(pathValue.isString()){

                    //取到字幕文件的路径
                    QString subtitlePath = pathValue.toString();
                    subtitle=new DivideStr2dict();
                    subtitle->get_word_frequency(subtitlePath);
                }
            }
        }
    }
}

