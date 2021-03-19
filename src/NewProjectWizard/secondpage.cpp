#include "secondpage.h"
#include "ui_secondpage.h"

SecondPage::SecondPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondPage)
{
    ui->setupUi(this);
    make_connect();
}

SecondPage::~SecondPage()
{
    delete ui;
    delete mainWindow;
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
}

void SecondPage::on_open_subtittle_button_clicked()
{
    QString fileName = FileOperate::openFile(nullptr,FileOperate::SUBTITTLE_FILE);
    ui->subtitleComboBox->addItem(fileName);
}

void SecondPage::on_create_project_button_clicked()
{
    mainWindow = new MainWindow();
    this->close();
    mainWindow->show();
}
