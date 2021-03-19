#include "firstpage.h"
#include "ui_firstpage.h"
#include "config/newproject_config.h"

FirstPage::FirstPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstPage)
{
    ui->setupUi(this);
    //隐藏菜单栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //初始化信号槽
    make_connect();
    init_edit();//初始化输入框内容

}

FirstPage::~FirstPage()
{
    delete ui;
    delete importFilePage;
}

void FirstPage::on_next_step_clicked(){
    //检测项目名以及路径是否合法
    QString projectName=ui->projectNameEdit->text();
    QString projectPath=ui->projectPositionEdit->text();
    if(projectPath==""){
        QMessageBox::warning(this, tr("警告"),tr("项目路径不能为空"),QMessageBox::Ok);
        return;
    }

    //检测下一个页面是否已经存在
    if(importFilePage==nullptr){
        importFilePage = new SecondPage(this);
        importFilePage->show();
    }else{
        importFilePage->show();
    }

}
void FirstPage::on_choose_project_path_clicked(){
    //打开选择文件对话框获取存储路径
    QString projectPath = FileOperate::openDirectory();
    ui->projectPositionEdit->setText(projectPath);
}

void FirstPage::init_edit(){
    //设置输入框正则表达式
#ifdef Q_OS_WIN32
    QRegularExpression projectPathReg("^[a-zA-Z]:([\\\\/][^\\s\\\\/:*?<>\"|][^\\\\/:*?<>\"|]*)*([/\\\\])?$");
#elif
    QRegularExpression projectPathReg("^\/(\w+\/?)+$");
#endif

    QRegularExpression projectNameReg("^[^?？\\*|“<>:/]{1,256}$");
    QValidator *projectPathValidator=new QRegularExpressionValidator(projectPathReg,this);
    QValidator *projectNameValidator=new QRegularExpressionValidator(projectNameReg,this);
    ui->projectNameEdit->setValidator(projectNameValidator);
    ui->projectPositionEdit->setValidator(projectPathValidator);

    //设置项目名称为MyProject + 编号
    QString projectName=DEFAULT_PROJECT_NAME;
    for (unsigned int i=1; ;i++ ) {
        if(i!=1){
            projectName=DEFAULT_PROJECT_NAME+QString::number(i);
        }
        QFileInfo dir(DEFAULT_PROJECT_PATH+"\\"+projectName);
        if(!dir.exists()){
            break;
        }
    }
    ui->projectNameEdit->setText(projectName);
    ui->projectPositionEdit->setText(DEFAULT_PROJECT_PATH+"/"+projectName);
}

void FirstPage::make_connect(){
    //下一步按钮
    QObject::connect(ui->nextStepButton,&QPushButton::clicked,this,&FirstPage::on_next_step_clicked);

    //取消按钮
    QObject::connect(ui->cancelButton,&QPushButton::clicked,this,&FirstPage::close);

    //选择项目存储位置
    QObject::connect(ui->chooseProjectPathButton,&QPushButton::clicked,this,&FirstPage::on_choose_project_path_clicked);

}
