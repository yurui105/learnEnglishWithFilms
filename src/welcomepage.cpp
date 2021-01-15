#include "welcomepage.h"
#include "ui_welcomepage.h"


WelcomePage::WelcomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomePage)
{
    ui->setupUi(this);
    //初始化信号槽
    makeConnect();
}

WelcomePage::~WelcomePage()
{
    delete ui;
    delete patronPage;
}

void WelcomePage::openGithubURL(){
    //打开项目github地址
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/yurui105/learnEnglishWithFilms")));
}

void WelcomePage::openPatron(){
    patronPage = new PatronPage(this);
    patronPage->show();

}

void WelcomePage::makeConnect(){
    //绑定打开github按钮
    QObject::connect(ui->githubButton,&QPushButton::clicked,this,&WelcomePage::openGithubURL);
    //绑定赞助按钮
    QObject::connect(ui->patronButton,&QPushButton::clicked,this,&WelcomePage::openPatron);

}
