#include"videocutthread.h"
#include<QThread>
#include<QProcess>
#include<QStringList>
#include<QDir>
#include<QTime>

void VideoCutThread::closeThread()
{
	isStop = true;
}

VideoCutThread::VideoCutThread(QObject* parent) :
	QObject(parent),
	isStop(false)
{

}

//QVector<pair<QString, QString>> time
void VideoCutThread::startWoker() {
	//创建数据目录
	QString data_path = project_path + "/" + "data" + "/";
	QDir dir(data_path);
	if (!dir.exists()) {
		dir.mkdir(data_path);
	}
	QString program = "E:/learnEnglishWithFilms/bin/ffmpeg.exe";
	for (auto it : time) {

		QTime begin_time = QTime::fromString(it.first, "hh:mm:ss");
		QTime end_time = QTime::fromString(it.first, "hh:mm:ss");
		QTime m_time;
		m_time.setHMS(0, 0, 0, 0);
		m_time.addSecs(end_time.secsTo(begin_time));
		QString time_long = m_time.toString("hh:mm:ss");

		QProcess po(0);
		qDebug() << it.first << "\t" << it.second;
		QStringList argu;

		argu.append("-i");
		argu.append(this->video_path);
		argu.append("-ss");
		argu.append(it.first);
		argu.append("-to");
		argu.append(it.second);
		argu.append("-acodec");
		argu.append("copy ");

		//argu.append("-vcodec");
		//argu.append("copy ");
		
		
		QString first = it.first.replace(QString(":"), QString(""));
		QString second = it.second.replace(QString(":"), QString(""));
		argu.append(data_path+first+"-"+second+".mp4");

		po.start(program,argu);
		po.waitForFinished();
		QString result = po.readAllStandardOutput();

		qDebug() << "error:\t" << po.readAllStandardError();
		qDebug() <<"result:\t" <<result;
	}
}