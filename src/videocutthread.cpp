#include"videocutthread.h"
#include<QThread>
#include<QProcess>
#include<QStringList>
#include<QDir>
#include<QTime>
#include<cstdlib>
#ifdef Q_OS_WIN32
#include<Windows.h>
#endif
#include<QProcess>
#include<string>

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

	int i = 1;
	for (QVector<std::pair<QString, QString>>::iterator it = time.begin(); it != time.end(); it++, i++) {
		//计算剪辑时长
		int s = QTime().fromString(it->first, "hh:mm:ss").secsTo(QTime().fromString(it->second, "hh:mm:ss"));
		QTime temp = QTime(0, 0, 0).addSecs(s+2);
		QString duration = temp.toString("hh:mm:ss");

		//组合文件名
		QString first = it->first;
		first = first.replace(QString(":"), QString(""));
		QString second = it->second;
		second = second.replace(QString(":"), QString(""));
		QString out = data_path + first + "-" + second + ".mp4";
		


#ifdef Q_OS_WIN32
        QString para = QString("/c ffmpeg -y -ss %1 -t %2 -i %3 -codec copy %4").arg(it->first,duration,video_path,out);
		SHELLEXECUTEINFO ShExecInfo = { 0 };
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = (LPCWSTR)L"open";
		ShExecInfo.lpFile = (LPCWSTR)L"cmd";
		ShExecInfo.lpParameters = (LPCWSTR)para.unicode();
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_HIDE;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
#elif Q_OS_OSX
        QString para = QString("/c ffmpeg -y -ss %1 -t %2 -i %3 -codec copy %4").arg(it->first,duration,video_path,out);
        //构造参数
        QProcess p(nullptr);
        QStringList arg;
        arg.append("-y");
        arg.append("-ss");
        arg.append(it->first);
        arg.append("-t");
        arg.append(duration);
        arg.append("-i");
        arg.append(video_path);
        arg.append("-codec");
        arg.append("copy");
        arg.append(out);
        //执行命令
        p.start("ffmpeg",arg);
        p.waitForFinished();
        qDebug()<<QString::fromLocal8Bit(p.readAllStandardError());

#endif
        qDebug()<<i;
		emit progress(i);
	}
}
