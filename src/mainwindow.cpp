#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QStandardItemModel>
#include"welcomepage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,isNewProject(true)
{
    ui->setupUi(this);
    QObject::connect(this, &MainWindow::startThread_signal, this, &MainWindow::openThreadSlot);
    connect(ui->words_table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(on_word_table_click(int,int)));

    //视频播放信号槽
    timer = new QTimer(this);
    connect(this,SIGNAL(setMedia(QString)),this,SLOT(loadMedia(QString)));
    connect(timer,&QTimer::timeout,this,&MainWindow::timeout_update);
    connect(ui->volumeSlider,SIGNAL(valueChanged(int)),this,SIGNAL(on_horizontalSlider_Volume_valueChanged(int)));
    connect(ui->pushButton_play,&QPushButton::clicked,this,&MainWindow::on_pushButton_play_clicked);
    connect(ui->pushButton_pause,&QPushButton::clicked,this,&MainWindow::on_pushButton_pause_clicked);
    connect(ui->pushButton_reset,&QPushButton::clicked,this,&MainWindow::on_pushButton_reset_clicked);
    connect(ui->pushButton_stop,&QPushButton::clicked,this,&MainWindow::on_pushButton_stop_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_project_status(bool status)
{
    isNewProject=status;
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
    connect(cutThread, SIGNAL(progress(int)), this, SLOT(process(int)));
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

void MainWindow::process(int a)
{
    if (a < subtitle->getOccurrencesTime().size()) {
        //更新当前进度
        ui->progressBar->setValue(a);
        qDebug() << "main thread:" << a;
    }
    else {
        //进度完成，隐藏进度条
        ui->progressBar->setVisible(false);
        ui->progress_label->hide();
    }
}

void MainWindow::on_word_table_click(int x, int y)
{
    qDebug() << "双击表格:" << x << ":" << y;
    //获取表格内容
    QVector<QString> time;
    QString word = ui->words_table->item(x,1)->text();

    tvector=subtitle->get_sorted_sequence();
    for(QVector<std::pair<QString, time_fre>>::iterator it = tvector.begin();it!=tvector.end();it++){
        if(it->first==word){
            current=0;
            time.clear();
            time=it->second.time;
            break;
        }
    }

    //将时间信息变换为文件名字
    //时间类型：00:01:21,541 --> 00:01:23,291
    std::regex pattern("[0-9]{2}:[0-9]{2}:[0-9]{2}");
    for(auto it:time){
        std::string temp = it.toStdString();
        std::smatch result;
        std::string::const_iterator itBegin = temp.begin();
        std::string::const_iterator itEnd = temp.end();

        QVector<QString> time;

        while (regex_search(itBegin,itEnd, result, pattern)) {
            time.push_back(QString::fromStdString(result[0]));
            itBegin = result[0].second;
        }//while
        play_time.push_back(time[0].replace(":","")+"-"+time[1].replace(":","")+".mp4");
    }
    //设置播放的文件
    qDebug()<<project_path+"/data/"+play_time[current%play_time.size()]+".mp4";
    emit setMedia(project_path+"/data/"+play_time[current%play_time.size()]+".mp4");
    current++;

}

void MainWindow::init_subtitle()
{
    //初始化字幕数据
    analysis_subtitle();
    //设置词频表
    setWordsTable();


    //新线程处理视频
    if(isNewProject){
        //如果该项目为第一次创建，则剪切视频
        //如果该项目为已经创建的项目，则不进行视频剪切
        emit startThread_signal();
    }

}

void MainWindow::setWordsTable()
{
    //设置词频表格
    QVector<std::pair<QString, time_fre>> words = subtitle->get_sorted_sequence();
    int i=0;
    for(auto it = words.begin();it!=words.end();it++){
        ui->words_table->insertRow(i);
        ui->words_table->setItem(i,0,new QTableWidgetItem(QString::number(i + 1)));
        ui->words_table->setItem(i,1,new QTableWidgetItem(it->first));
        ui->words_table->setItem(i,2,new QTableWidgetItem(QString::number(it->second.frequency)));
        i++;
    }
    
    //设置进度条进度
    int maxProgress = subtitle->getOccurrencesTime().size();
    ui->progressBar->setMaximum(maxProgress);

    //演示专用
    QVector<std::pair<QString, QString>> time = subtitle->getOccurrencesTime();
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

//播放
void MainWindow::on_pushButton_play_clicked()
{
    ui->openGLWidget->play();
    timer->start(100);
}

//停止播放
void MainWindow::on_pushButton_stop_clicked()
{
    ui->openGLWidget->stop();
}

////静音
//void MainWindow::on_pushButton_Volume_clicked()
//{
//    static bool value=false;
//    value=!value;
//    ui->openGLWidget->setMute(value);
//}

void MainWindow::on_pushButton_reset_clicked()
{
    ui->openGLWidget->seek(0);
    ui->openGLWidget->play();
    timer->start(100);
}


void MainWindow::on_pushButton_pause_clicked()
{
    timer->stop();
    ui->openGLWidget->pause();
}

void MainWindow::loadMedia(QString filepath){
    ui->openGLWidget->setMedia(filepath);
    ui->openGLWidget->play();
    QThread::msleep(100);
    //设置总时间
    ui->label->setText(QString("%1").arg(ui->openGLWidget->duration()));

    //设置进度条滑块范围
    ui->playerSlider->setMinimum(0);
    ui->playerSlider->setMaximum(ui->openGLWidget->duration());
    current_video_duration=ui->openGLWidget->duration();

    //事件监听
    ui->playerSlider->installEventFilter(this);

    //开启定时器
    timer->start(100);

}

void MainWindow::timeout_update()
{
    int64_t pos=ui->openGLWidget->position();
    ui->playerSlider->setValue(pos);
    // 设置时间
    ui->label->setText(QString("%1").arg(pos));

    //判断当前视频是否播放完毕，是的话则播放下一个视频
    if(pos==current_video_duration-1){
        qDebug()<<project_path+"/data/"+play_time[current%play_time.size()]+".mp4";
        emit setMedia(project_path+"/data/"+play_time[current%play_time.size()]+".mp4");
        current++;
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->playerSlider)
    {
        if (event->type()==QEvent::MouseButtonPress)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
               int value = QStyle::sliderValueFromPosition(ui->playerSlider->minimum(), ui->playerSlider->maximum(), mouseEvent->pos().x(), ui->playerSlider->width());
               ui->playerSlider->setValue(value);

               //跳转播放器
               ui->openGLWidget->seek(value);
            }
        }
    }
    return QObject::eventFilter(obj,event);
}
void MainWindow::on_horizontalSlider_Volume_valueChanged(int value)
{
     ui->openGLWidget->setVolume(float(value/10.0));
}
