#include "dividestr2dict.h"
#include<QDebug>
#include<QMessageBox>
#include<QTextStream>
#include<qregularexpression.h>
#include<regex>
#include<QTime>
#include<string>
DivideStr2dict::DivideStr2dict()
{
    
}


/// <summary>
/// 对str文件格式进行词频统计
/// </summary>
/// <param name="filepath">str文件路径</param>
void DivideStr2dict::get_word_frequency(QString filepath)
{

    QFile inFile(filepath);
    if(!inFile.open(QIODevice::ReadOnly)){
            QMessageBox::warning(nullptr,"read file",QObject::tr("read file fail.%1").arg(inFile.errorString()));
            return;
      }
    QTextStream in(&inFile);

    int i=1;
    while (!in.atEnd()) {
        QString line;
        line=in.readLine();
        if(0==line.compare(QString::number(i))){
            i++;
            qDebug() << "i:" << i;
            QString time;
            time=in.readLine();
            time_vec.push_back(time);
            while (true) {
                line=in.readLine();
                if(!line.isEmpty()){
                    analysis_line(line+"  ",time);
                }
                else
                {
                    break;
                }
            }
        }
    }
    qDebug()<<"close"<<"\n";
    inFile.close();

    
    for (auto it = words.begin(); it != words.end(); it++) {
        tvector.push_back(std::make_pair(it->first, it->second));
    }
    sort(tvector.begin(), tvector.end(), cmp);
    processTime();
}
/// <summary>
/// 输出unordered_map内容
/// </summary>
/// <param name="a">unordered_map结构数据</param>
//void DivideStr2dict::print_dict(vector<pair<string, time_fre>> a) {
//    for (auto it = a.begin(); it != a.end(); it++) {
//        qDebug() << it->first << ":" << it->second.frequency << endl;
//    }
//}

void DivideStr2dict::processTime()
{
    std::regex pattern("[0-9]{2}:[0-9]{2}:[0-9]{2}");
    for (auto it = time_vec.begin(); it != time_vec.end(); it++) {
        std::string temp = (*it).toStdString();
        std::smatch result;
        std::string::const_iterator itBegin = temp.begin();
        std::string::const_iterator itEnd = temp.end();

        QVector<QString> time;

        while (regex_search(itBegin,itEnd, result, pattern)) {
            time.push_back(QString::fromStdString(result[0]));
            itBegin = result[0].second;
        }//while

        occurrences_time.push_back(std::make_pair(time[0], time[1]));
        time.clear();
    }
}

/// <summary>
/// 判断字符是否是分词符号
/// </summary>
/// <param name="c">待匹配的字符</param>
/// <returns>返回匹配结果</returns>
bool DivideStr2dict::is_in(char c) {
    std::string rule = "\'\"?\\/?!@#$%^&*()<>[]{},.;:-_";
    for (unsigned int i = 0; i < rule.size(); i++) {
        if (c == rule[i]) {
            return true;
        }
        return false;
    }
}

/// <summary>
/// 统计单个句子中的词频
/// </summary>
/// <param name="s"></param>
void DivideStr2dict::analysis_line(QString s,QString time) {
    for (unsigned int i = 0; i < s.size();) {
        for (unsigned int j = 0; j < s.size(); j++) {
            if ((s[j]>='a'&&s[j]<='z')||(s[j]>='A'&&s[j]<='Z')) {
                continue;
            }
            else
            {
                QString word = s.mid(i, j - i);
                //转为小写
                word = word.toLower();
                //判断单词长度
                if (word.size() >1) {
                    if (words.find(word) != words.end()) {
                        words[word].frequency++;
                        words[word].time.push_back(time);
                    }
                    else
                    {
                        words[word].frequency = 1;
                        words[word].time.push_back(time);
                    }
                }
                i = j + 1;
            }
        }
    }
}

int DivideStr2dict::cmp(const std::pair<QString, time_fre> &a, const std::pair<QString, time_fre> &b) {
    return a.second.frequency < b.second.frequency;
}
