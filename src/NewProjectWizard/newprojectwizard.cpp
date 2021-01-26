#include "newprojectwizard.h"
#include "ui_newprojectwizard.h"

NewProjectWizard::NewProjectWizard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewProjectWizard)
{
    ui->setupUi(this);
}

NewProjectWizard::~NewProjectWizard()
{
    delete ui;
}
