#ifndef OPENPROJECT_H
#define OPENPROJECT_H
#include<QString>
#include<QJsonDocument>
#include<QFile>
#include<QMessageBox>

class OpenProject
{
public:
    OpenProject(QString path);
    QJsonDocument get_project_config() const{
        return project_config;
    }
    bool status();

private:
    bool fileStatus;
    QJsonDocument project_config;
};

#endif // OPENPROJECT_H
