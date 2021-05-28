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
    wizard.setWelcomePage(this);
    if(wizard.isAllWidgetHide()){
        wizard.showFitsrPage();
        this->hide();
    }
}

void WelcomePage::openProject()
{
    QString fileName = FileOperate::openFile(nullptr,FileOperate::PROJECT_FILE);
    if(fileName.isEmpty()){
        return;
    }
    OpenProject config(fileName);
    //判断该文件是否有问题
    if(!config.status()){
        QMessageBox::warning(this,"打开项目失败","打开项目"+fileName+"\n请检查",QMessageBox::Ok);
        return;
    }
    //初始化主界面
    MainWindow *mainWindow = new MainWindow();
    mainWindow->set_project_config(config.get_project_config());
    mainWindow->set_project_status(false);
    mainWindow->init_subtitle();
    mainWindow->show();
    this->close();
}
void WelcomePage::makeConnect(){
    //绑定打开github按钮
    QObject::connect(ui->githubButton,&QPushButton::clicked,this,&WelcomePage::openGithubURL);
    //绑定赞助按钮
    QObject::connect(ui->patronButton,&QPushButton::clicked,this,&WelcomePage::openPatron);

    //新建项目按钮
    QObject::connect(ui->newProjectButton,&QPushButton::clicked,this,&WelcomePage::newProject);
    QObject::connect(ui->openProjectButton,&QPushButton::clicked,this,&WelcomePage::openProject);
}
