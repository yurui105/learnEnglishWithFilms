#include "fileoperate.h"

FileOperate::FileOperate()
{
}

///
/// \brief FileOperate::openDirectory
/// \param DEFAULT_PATH(current path)
/// \return the path of directoty(type QString)
///
QString FileOperate::openDirectory(QString DEFAULT_PATH)
{
    QString path;
    if(DEFAULT_PATH.isEmpty()){
        DEFAULT_PATH = "./";
    }
    path = QFileDialog::getExistingDirectory(nullptr,
                                             QObject::tr("选择路径"),
                                             DEFAULT_PATH,
                                             QFileDialog::ShowDirsOnly);

    return path;
}

///
/// \brief FileOperate::openFile
/// \param filePath
/// \param fileType
/// \return the path of openfile
///
QString FileOperate::openFile(QString filePath,QString fileType)
{
    if(filePath.isEmpty()){
        filePath = "./";
    }
    if(fileType.isEmpty()){
        fileType=FileOperate::ALL_FILE;
    }
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QObject::tr("选择文件"),
                                                    filePath,
                                                    fileType);
    return fileName;

}

bool FileOperate::createFile(QString name,QString type,QString path){
    //判断文件是否已经存在，存在则返回创建失败
    QFileInfo fileInfo(path+"/"+name+"."+type);
    if(fileInfo.isFile()){
        return false;
    }

    //检查路径是否存在，不存在则创建目录
    QDir dir(path);
    if(!dir.exists()){
        dir.mkdir(path);
    }

    //创建文件
    QFile file(path+"/"+name+"."+type);
    file.open(QIODevice::WriteOnly);
    file.close();
    return true;
}
