#include "secondpage.h"
#include "ui_secondpage.h"
#include"media/videoinformation.h"

SecondPage::SecondPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondPage),
    audioInVideo(true),
    subttileInVideo(true)
{
    ui->setupUi(this);
    //隐藏菜单栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    make_connect();
}

SecondPage::~SecondPage()
{
    delete ui;
}


void SecondPage::make_connect(){
    //点击上一步按钮，隐藏当前页面
    QObject::connect(ui->preStepButton,&QPushButton::clicked,this,&SecondPage::hide);
    QObject::connect(ui->openFileButton,&QPushButton::clicked,this,&SecondPage::on_open_file_button_clicked);
    QObject::connect(ui->openAudioButton,&QPushButton::clicked,this,&SecondPage::on_open_audio_button_clicked);
    QObject::connect(ui->openSubtitteButton,&QPushButton::clicked,this,&SecondPage::on_open_subtittle_button_clicked);
    QObject::connect(ui->createProjectButton,&QPushButton::clicked,this,&SecondPage::on_create_project_button_clicked);
}

void SecondPage::on_open_file_button_clicked()
{
    QString fileName = FileOperate::openFile(nullptr,FileOperate::VIDEO_FILE);
    if(fileName.isEmpty()){
        return;
    }

    //设置视频信息
    ui->fileNameEdit->setText(fileName);
    VideoInformation info;
    info.getVideoInfo(fileName);
    ui->time_lable->setText(info.getDuration());
    ui->bitrate_label->setText(QString::number(info.getVideoAverageBitRate()));
    ui->format_label->setText(info.getFormat());
    ui->encode_label->setText(info.getVideoFormat());
    ui->resolution_label->setText(QString::number(info.getWidth())+" X "+QString::number(info.getHeight()));

    //判断是否有音频信息
    if(!info.getAudioFormat().isEmpty()&&!info.getSampleRate().isEmpty()){
        ui->audioBitrate_label->setText(QString::number(info.getAudioAverageBitRate()[0]));
        ui->audioSampleRate_label->setText(QString::number(info.getSampleRate()[0]));

    }

    //设置音频下拉框
    QVector<QString> audio_format=info.getAudioFormat();
    for(auto i = audio_format.begin();i!=audio_format.end();i++){
        ui->audioComboBox->addItem(*i);
    }

    //设置字幕下拉框
    QVector<QString> subtitle_format = info.getSubtitleFormat();
    for(auto i = subtitle_format.begin();i!=subtitle_format.end();i++){
        ui->subtitleComboBox->addItem(*i);
    }
}

void SecondPage::on_open_audio_button_clicked()
{
    QString fileName = FileOperate::openFile(nullptr,FileOperate::AUDIO_FILE);
    if(fileName.isEmpty()){
        return;
    }

    ui->audioComboBox->addItem(fileName);
    int last = ui->audioComboBox->count();
    ui->audioComboBox->setCurrentIndex(last);
    audioInVideo = false;

    VideoInformation info;
    info.getVideoInfo(fileName);
    ui->audioBitrate_label->setText(QString::number(info.getAudioAverageBitRate()[0]));
    ui->audioSampleRate_label->setText(QString::number(info.getSampleRate()[0]));
}

void SecondPage::on_open_subtittle_button_clicked()
{
    QString fileName = FileOperate::openFile(nullptr,FileOperate::SUBTITTLE_FILE);
    if(fileName.isEmpty()){
        return;
    }

    ui->subtitleComboBox->addItem(fileName);
    int last = ui->subtitleComboBox->count();
    ui->subtitleComboBox->setCurrentIndex(last-1);
    subttileInVideo = false;
    VideoInformation info;
    info.getVideoInfo(fileName);
}

void SecondPage::on_create_project_button_clicked()
{
    //判断必要信息是否存在
    if(ui->fileNameEdit->text().isEmpty()){
        QMessageBox::warning(this,tr("警告"),tr("请选择视频文件！"));
        return;
    }else if(ui->audioComboBox->currentText().isEmpty()){
        QMessageBox::warning(this,tr("警告"),tr("请选择音频文件！"));
        return;
    }else if(ui->subtitleComboBox->currentText().isEmpty()){
        QMessageBox::warning(this,tr("警告"),tr("请选择字幕文件！"));
        return;
    }



    NewProjectWizard &wizard = NewProjectWizard::getInstance();
    wizard.setVideoPath(ui->fileNameEdit->text());
    wizard.setAudioPath(audioInVideo,ui->audioComboBox->currentText());
    wizard.setSubtittlePath(subttileInVideo,ui->subtitleComboBox->currentText());

    wizard.savaData();

    mainWindow = new MainWindow();
    mainWindow->set_project_config(wizard.get_project_config());
    mainWindow->init_subtitle();
    mainWindow->show();
    wizard.closeWizard();
}
