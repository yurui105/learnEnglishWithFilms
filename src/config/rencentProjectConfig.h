#ifndef RENCENTPROJECTCONFIG_H
#define RENCENTPROJECTCONFIG_H
#include<QString>
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>

#include"config/newproject_config.h"

QVariantMap openJson();

void upadteRencentProject(QString curent){
    QVariantMap map=openJson();
    if(map.isEmpty()){
        return;
    }
    map.value(curent).toString();

}

void addRencentProject(QString filePath){
    QVariantMap map=openJson();
    if(map.isEmpty()){
        return;
    }
}

QVariantMap openJson(){
    QVariantMap map;
    QString file_path=DEFAULT_PROJECT_PATH+"/lef.conf";
    //1、打开配置文件
    QFile file(file_path);
    file.open(QIODevice::ReadOnly);
    QByteArray data=file.readAll();
    file.close();
    //使用json文件对象加载字符串
    QJsonDocument doc=QJsonDocument::fromJson(data);

    if(doc.isNull()){
        return map;
    }

    QJsonObject obj=doc.object();
    map=obj.toVariantMap();
    return map;

}

#endif // RENCENTPROJECTCONFIG_H
