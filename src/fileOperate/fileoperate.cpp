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
