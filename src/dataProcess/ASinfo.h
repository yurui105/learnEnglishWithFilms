#ifndef ASINFO_H
#define ASINFO_H
#include<QString>

//ASinfo类用来存储音频/字幕信息，因为某些视频文件中会包含很多音轨以及字幕文件
//如果音频/字幕文件来源于视频文件，则将includeInVideo设置为true，同时设置name属性指定音轨/字幕
//如果音频/字幕文件来自于用户选择文件，则将includeInVideo设置为false，同时设置filepath属性为文件路径
typedef struct ASinfo{
    bool includeInVideo;
    QString filePath;
    QString name;
}ASinfo;

#endif // ASINFO_H
