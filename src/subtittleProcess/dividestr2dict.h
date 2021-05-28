#ifndef DIVIDESTR2DICT_H
#define DIVIDESTR2DICT_H

#include<QVector>
#include<QString>
#include<unordered_map>
#include<QFile>
#include <algorithm>
#include<QDebug>
//using namespace std;

class time_fre {
public:
    int frequency;
    QVector<QString> time;
};

class DivideStr2dict
{
public:
    DivideStr2dict();
    void get_word_frequency(QString filepath);
    const QVector<std::pair<QString, time_fre>>& get_sorted_sequence(){
        return tvector;
    }
    QVector<std::pair<QString, QString>> getOccurrencesTime() {
        return occurrences_time;
    }
private:
    //保存单词词频
    std::unordered_map<QString, time_fre> words;
    //按词频排序后的序列，没有时间信息
    QVector<std::pair<QString, time_fre>> tvector;
    QVector<QString> time_vec;
    QVector<std::pair<QString, QString>> occurrences_time;
    void processTime();


private:
//    void print_dict(vector<pair<string, time_fre>> a);
    bool is_in(char c);
    void analysis_line(QString s,QString time);
    static int cmp(const std::pair<QString, time_fre> &a, const std::pair<QString, time_fre> &b);

};

#endif // DIVIDESTR2DICT_H
