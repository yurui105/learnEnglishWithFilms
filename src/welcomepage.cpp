#include "welcomepage.h"
#include "ui_welcomepage.h"


WelcomePage::WelcomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomePage)
{
    ui->setupUi(this);
    signalMapper = new QSignalMapper(this);

    //初始化信号槽
    makeConnect();
    //初始化最近打开项目界面
    initRecentProject();
}

WelcomePage::~WelcomePage()
{
    delete ui;
}

void WelcomePage::initRecentProject()
{


    std::unordered_map<QString,QString> recent;
    QString file_path=DEFAULT_PROJECT_PATH+"/lef.conf";
    //1、打开配置文件
    QFile file(file_path);
    file.open(QIODevice::ReadOnly);
    QByteArray data=file.readAll();
    file.close();
    //使用json文件对象加载字符串
    QJsonDocument doc=QJsonDocument::fromJson(data);
    //判断是否对象
    if(doc.isObject()){
        //把json文档转换为json对象
        QJsonObject obj=doc.object();
        recent_project=obj;
        if(obj.contains("1")){
            ui->recent1->setText(obj.value("1").toString());
        }else{
            ui->recent1->hide();
        }
        if(obj.contains("2")){
            ui->recent2->setText(obj.value("2").toString());
        }else{
            ui->recent2->hide();
        }
        if(obj.contains("3")){
            ui->recent3->setText(obj.value("3").toString());
        }else{
            ui->recent3->hide();
        }
        if(obj.contains("4")){
            ui->recent4->setText(obj.value("4").toString());
        }else{
            ui->recent4->hide();
        }
        if(obj.contains("5")){
            ui->recent5->setText(obj.value("5").toString());
        }else{
            ui->recent5->hide();
        }
    }else{
        ui->recent1->hide();
        ui->recent2->hide();
        ui->recent3->hide();
        ui->recent4->hide();
        ui->recent5->hide();
    }

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

void WelcomePage::openRecentProject(QString i)
{
    qDebug()<<i;
    OpenProject config(recent_project.value(i).toString());
    //判断该文件是否有问题
    if(!config.status()){
        QMessageBox::warning(this,"打开项目失败","打开项目"+recent_project.value(i).toString()+"\n请检查",QMessageBox::Ok);
        return;
    }
    //初始化主界面
    MainWindow *mainWindow = new MainWindow();
    mainWindow->set_project_config(config.get_project_config());
    mainWindow->init_subtitle();
    mainWindow->set_project_status(false);
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
    connect(ui->recent1, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->recent1, "1");

    connect(ui->recent2, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->recent2, "2");

    connect(ui->recent3, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->recent3, "3");

    connect(ui->recent4, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->recent4, "4");

    connect(ui->recent5, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->recent5, "5");

    connect(signalMapper, &QSignalMapper::mappedString,this, &WelcomePage::openRecentProject);
}
