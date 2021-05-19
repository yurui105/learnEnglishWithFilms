#pragma once
#include<QObject>
#include<QVector>
#include<QString>
#include <QProcess>
#include <QDebug>
using namespace std;

class VideoCutThread :public QObject {
	Q_OBJECT
public:
	explicit VideoCutThread(QObject* parent = nullptr);
	void closeThread();
	void set_time(QVector<pair<QString, QString>> t) {
		time = t;
	}
	void setPath(QString p) { project_path = p; }
	void setVideoPath(QString p) { video_path = p; }

public slots:
	void startWoker();

private:
	volatile bool isStop;
	QVector<pair<QString, QString>> time;
	QString project_path;
	QString video_path;

};

