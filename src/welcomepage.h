#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include<QWidget>
#include<QUrl>
#include<QDesktopServices>
#include<QPushButton>
#include<QMessageBox>
#include<QJsonDocument>
#include<QSignalMapper>
#include"patronpage.h"
#include"NewProjectWizard/firstpage.h"
#include"fileOperate/openproject.h"
#include"config/newproject_config.h"
#include"mainwindow.h"

namespace Ui {
class WelcomePage;
}

class WelcomePage : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomePage(QWidget *parent = nullptr);
    ~WelcomePage();

private:
    Ui::WelcomePage *ui;
    PatronPage *patronPage;//赞赏界面
//    FirstPage *newProjectPage;//新建项目界面
    void initRecentProject();
    QSignalMapper *signalMapper;//主要用作设置点击不同的按钮发送不同的数字
    QJsonObject recent_project;


    //配置信号槽
    void makeConnect();

public slots:
    //打开github
    void openGithubURL();
    //赞助界面
    void openPatron();
    //新建项目
    void newProject();
    //打开项目
    void openProject();
    void openRecentProject(QString i);
};

#endif // WELCOMEPAGE_H
