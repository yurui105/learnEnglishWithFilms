#ifndef NEWPROJECTWIZARD_H
#define NEWPROJECTWIZARD_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QWizardPage>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "costomMessageBox/messagebox.h"
#include "NewProjectWizard/secondpage.h"
#include "fileOperate/fileoperate.h"
#include "NewProjectWizard/wizard.h"



namespace Ui {
class FirstPage;
}

class FirstPage : public QWidget
{
    Q_OBJECT

public:
    explicit FirstPage(QWidget *parent = nullptr);
    ~FirstPage();

private:
    //初始化信号槽
    void make_connect();
    void init_edit();//初始化输入框内容
    Ui::FirstPage *ui;

private slots:
    //下一步按钮
    void on_next_step_clicked();
    void on_choose_project_path_clicked();
};


#endif // NEWPROJECTWIZARD_H
