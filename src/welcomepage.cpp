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
}

void WelcomePage::openGithubURL(){
    //打开项目github地址
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/yurui105/learnEnglishWithFilms")));
}

void WelcomePage::openPatron(){
    patronPage = new PatronPage(this);
    patronPage->show();

}

void WelcomePage::newProject(){
//    newProjectPage = new FirstPage(this);

//    newProjectPage->show();

    //新建项目向导类初始化，并显示第一个界面
    //NewProjectWizard类采用sigleton设计
    //NewProject类的构造函数中默认对第一个界面进行显示，所以只需实例化该类即可
    NewProjectWizard &wizard = NewProjectWizard::getInstance();
    if(wizard.isAllWidgetHide()){
        wizard.showFitsrPage();
    }
}

void WelcomePage::makeConnect(){
    //绑定打开github按钮
    QObject::connect(ui->githubButton,&QPushButton::clicked,this,&WelcomePage::openGithubURL);
    //绑定赞助按钮
    QObject::connect(ui->patronButton,&QPushButton::clicked,this,&WelcomePage::openPatron);

    //新建项目按钮
    QObject::connect(ui->newProjectButton,&QPushButton::clicked,this,&WelcomePage::newProject);
}
