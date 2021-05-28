#pragma once
#include<QObject>
#include<QVector>
#include<QString>
#include <QProcess>
#include <QDebug>
////////

#include<stdio.h>
#include <stdlib.h>

///////
//using namespace std;

class VideoCutThread :public QObject {
	Q_OBJECT
public:
	explicit VideoCutThread(QObject* parent = nullptr);
	void closeThread();
	void set_time(QVector<std::pair<QString, QString>> t) {
		time = t;
	}
	void setPath(QString p) { project_path = p; }
	void setVideoPath(QString p) { video_path = p; }
	

signals:
	void progress(int);

public slots:
	void startWoker();

private:
	volatile bool isStop;
	QVector<std::pair<QString, QString>> time;
	QString project_path;
	QString video_path;

};

