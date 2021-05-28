#ifndef WIZARD_H
#define WIZARD_H

#include<QWidget>
#include<list>
#include<QJsonObject>
#include<QJsonDocument>

#include "NewProjectWizard/firstpage.h"
#include "NewProjectWizard/secondpage.h"
#include "fileOperate/fileoperate.h"
#include "costomMessageBox/messagebox.h"
#include "dataProcess/ASinfo.h"
#include "welcomepage.h"

class WelcomePage;

class NewProjectWizard:public QObject{
    Q_OBJECT
public:
    static NewProjectWizard& getInstance();
    ~NewProjectWizard();
public slots:
    void nextPage();
    void prevPage();
    void closeWizard();
    void savaData();
public:
    //设置项目相关变量
    void setProjectName(QString name){
        this->project_name = name;
    }
    void setProjectPath(QString path){
        this->project_path = path;
    }
    void setVideoPath(QString path){
        this->video_file_path = path;
    }

    void setAudioPath(bool includeInVideo,QString path){
        this->audio_file_path.includeInVideo=includeInVideo;
        if(includeInVideo==true){
            this->audio_file_path.name=path;
        }else{
            this->audio_file_path.filePath = path;
        }
    }

    void setSubtittlePath(bool includeInVideo,QString path){
        this->subtittle_file_path.includeInVideo=includeInVideo;
        if(includeInVideo==true){
            this->subtittle_file_path.name=path;
        }else{
            this->subtittle_file_path.filePath = path;
        }
    }
    bool isAllWidgetHide();
    void showFitsrPage();

    //获取项目相关变量
    QString getProjectName() const{
        return project_name;
    }
    QString getProjectPath() const{
        return project_path;
    }
    QString getVideoPath() const{
        return video_file_path;
    }
    ASinfo getAudioPath() const{
        return audio_file_path;
    }
    ASinfo getSubtittlePath() const{
        return subtittle_file_path;
    }

    void setWelcomePage(WelcomePage *page){
        welcome_instance=page;
    }

    QJsonDocument get_project_config(){
        return json_document;
    }

signals:
    void close_welcome_page();
    void let_main_window_init_subtitle();

private:
    NewProjectWizard();

    //pages用来存放两个向导界面的指针
    QList<QWidget *> pages;
    //curent指向当前激活的界面
    QList<QWidget *>::Iterator current;

    //项目文件所需资料目录
    QString project_name;
    QString project_path;
    QString video_file_path;
    ASinfo audio_file_path;
    ASinfo subtittle_file_path;

    //欢迎窗口界面
    WelcomePage* welcome_instance;

    //项目配置文件
    QJsonDocument json_document;

};

#endif
