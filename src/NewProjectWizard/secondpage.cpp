#include "secondpage.h"
#include "ui_secondpage.h"

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
    ui->fileNameEdit->setText(fileName);
}

void SecondPage::on_open_audio_button_clicked()
{
    QString fileName = FileOperate::openFile(nullptr,FileOperate::AUDIO_FILE);
    ui->audioComboBox->addItem(fileName);
    audioInVideo = false;
}

void SecondPage::on_open_subtittle_button_clicked()
{
    QString fileName = FileOperate::openFile(nullptr,FileOperate::SUBTITTLE_FILE);
    ui->subtitleComboBox->addItem(fileName);
    subttileInVideo = false;
}

void SecondPage::on_create_project_button_clicked()
{
    NewProjectWizard &wizard = NewProjectWizard::getInstance();
    wizard.setVideoPath(ui->fileNameEdit->text());
    wizard.setAudioPath(audioInVideo,ui->audioComboBox->currentText());
    wizard.setSubtittlePath(subttileInVideo,ui->subtitleComboBox->currentText());

    wizard.savaData();
    wizard.closeWizard();


    mainWindow = new MainWindow();
    mainWindow->show();
}
