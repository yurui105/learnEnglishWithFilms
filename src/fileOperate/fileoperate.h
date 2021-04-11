#ifndef FILEOPERATE_H
#define FILEOPERATE_H

#include <QString>
#include <QFileDialog>
#include <QObject>

class FileOperate
{
public:
    FileOperate();
    static QString openDirectory(QString DEFAULT_PATH="");
    static QString openFile(QString filePath = "",QString fileType="");
    static bool createFile(QString name,QString type,QString path);

    //打开文件类型
    inline static const QString VIDEO_FILE = "视频文件 (*.mp4 *.avi *.mkv)";
    inline static const QString SUBTITTLE_FILE = "字幕文件(*.str *.ass *.ass)";
    inline static const QString AUDIO_FILE = "音频文件(*.mp3 *.wav *.mp3 *.aac)";
    inline static const QString ALL_FILE = "所有文件(*.*)";
    inline static const QString PROJECT_FILE = "*.lef";
    inline static const QString JSON_FILE = "*.json";
};

#endif // FILEOPERATE_H
