#include "openproject.h"

OpenProject::OpenProject(QString path):fileStatus(false)
{
    //打开文件
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open failed!";
        QMessageBox::warning(nullptr,"打开文件失败","打开文件"+path+"失败\n请检查路径",QMessageBox::Ok);
    } else {
        qDebug() <<"File open successfully!";
    }
    QJsonParseError *error=new QJsonParseError;
    QJsonDocument jdc=QJsonDocument::fromJson(file.readAll(),error);

    //判断文件是否完整
    if(error->error!=QJsonParseError::NoError)
    {
        qDebug()<<"parseJson:"<<error->errorString();
        fileStatus=false;
    }else{
        project_config=jdc;
        fileStatus=true;
    }

}

bool OpenProject::status()
{
    return fileStatus;
}
