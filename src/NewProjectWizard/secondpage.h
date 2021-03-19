#ifndef SECONDPAGE_H
#define SECONDPAGE_H

#include <QWidget>
#include <QWizardPage>
#include <QPushButton>

#include "fileOperate/fileoperate.h"
#include "mainwindow.h"

namespace Ui {
class SecondPage;
}

class SecondPage : public QWidget
{
    Q_OBJECT

public:
    explicit SecondPage(QWidget *parent = nullptr);
    ~SecondPage();

private:
    Ui::SecondPage *ui;
    MainWindow *mainWindow;

    void make_connect();

private slots:
    void on_open_file_button_clicked();
    void on_open_audio_button_clicked();
    void on_open_subtittle_button_clicked();
    void on_create_project_button_clicked();
};

#endif // SECONDPAGE_H
