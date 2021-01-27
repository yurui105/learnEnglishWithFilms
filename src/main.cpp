#include "mainwindow.h"
#include"welcomepage.h"

#include"NewProjectWizard/importfiles.h"
#include"NewProjectWizard/newprojectwizard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImportFiles w;
    w.show();
    return a.exec();
}
