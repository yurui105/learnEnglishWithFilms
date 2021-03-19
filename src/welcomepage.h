#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>
#include<QUrl>
#include<QDesktopServices>
#include<QPushButton>

#include"patronpage.h"
#include"NewProjectWizard/firstpage.h"

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
    FirstPage *newProjectPage;//新建项目界面


    //配置信号槽
    void makeConnect();

public slots:
    //打开github
    void openGithubURL();
    //赞助界面
    void openPatron();
    //新建项目
    void newProject();
};

#endif // WELCOMEPAGE_H
