#include "NewProjectWizard/wizard.h"
#include <QDebug>
#include<QMessageBox>
NewProjectWizard::NewProjectWizard()
{
    //初始化向导界面,加入列表中
    pages.append(new FirstPage);
    pages.append(new SecondPage);
    if(!pages.isEmpty()){
        current = pages.begin();
    }
    (*current)->show();

    QObject::connect(this,&NewProjectWizard::close_welcome_page,welcome_instance,&WelcomePage::close);
}

NewProjectWizard &NewProjectWizard::getInstance()
{
    static NewProjectWizard instance;
    return instance;
}

void NewProjectWizard::nextPage()
{
    //当前页面为最后一个页面，直接返回
    if((*current) == pages.last()){
        return;
    }

    //如果不是最后一个窗口，则关闭当前窗口
    (*current)->close();
    //显示下一个窗口
    (*(++current))->show();
}

void NewProjectWizard::prevPage()
{
    if((*current)==pages.first()){
        return;
    }
    (*current)->close();
    (*(--current))->show();
}

void NewProjectWizard::closeWizard()
{
    emit let_main_window_init_subtitle();
    for(int i=0;i<pages.size();i++){
        qDebug()<<"析构向导页面"<<i<<":"<<pages[i];
        delete pages[i];
    }

    //
    if(welcome_instance!=nullptr){
        welcome_instance->close();
    }

}

//保存项目配置到文件
void NewProjectWizard::savaData()
{
    QJsonObject projectData;
    projectData.insert("ProjectName",project_name);
    projectData.insert("ProjectPath",project_path);
    projectData.insert("VideoPath",video_file_path);

    QJsonObject audioObject;
    audioObject.insert("IncludeInVideo",audio_file_path.includeInVideo);
    audioObject.insert("Path",audio_file_path.filePath);
    audioObject.insert("Name",audio_file_path.name);

    QJsonObject subtittleObject;
    subtittleObject.insert("IncludeInVideo",subtittle_file_path.includeInVideo);
    subtittleObject.insert("Path",subtittle_file_path.filePath);
    subtittleObject.insert("Name",subtittle_file_path.name);

    projectData.insert("AudioInfo",QJsonValue(audioObject));
    projectData.insert("SubtittleInfo",QJsonValue(subtittleObject));

    json_document.setObject(projectData);

    bool created = FileOperate::createFile(project_name,"lef",project_path);
    if(created){
        QFile file(project_path+"/"+project_name+".lef");
        if(file.open(QIODevice::ReadWrite)){
            file.write(json_document.toJson());
            file.close();
        }
        qDebug()<<"复制字幕文件"<<subtittle_file_path.filePath<<"到"<<"\t"+project_path+"/+subtitle.srt";
        QFile::copy(subtittle_file_path.filePath,project_path+"/+subtitle.srt");

    }else{
        // TO-DO
        QMessageBox::warning(nullptr,"无法创建文件","无法创建文件，请检查文件路径？",QMessageBox::Yes);
    }
}

bool NewProjectWizard::isAllWidgetHide()
{
    for(int i=0;i<pages.size();i++){
        if(!pages[i]->isHidden()){
            return false;
        }
    }
    return true;
}

void NewProjectWizard::showFitsrPage()
{
    current = pages.begin();
    (*current)->show();
}

NewProjectWizard::~NewProjectWizard()
{
    delete current;
}
