#pragma once
#include<QtOpenGLWidgets/qopenglwidget.h>
#include <memory>
#include<mdk/Player.h>

namespace mdk {
    class Player;
}
class QMDKWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    QMDKWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~QMDKWidget();
    void setDecoders(const QStringList& dec);
    void setMedia(const QString& url);
    void play();
    void pause();
    void stop();
    bool isPaused() const;
    void seek(qint64 ms, bool accurate = false);
    qint64 position() const;
    void snapshot();
    qint64 duration() const;
    void setVolume(float value);  //设置音量

    void prepreForPreview(); // load the media, and set parameters
signals:
    void mouseMoved(int x, int y);
    void doubleClicked();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent*) override;
    void mouseMoveEvent(QMouseEvent* ev) override;
    void mouseDoubleClickEvent(QMouseEvent*) override;
private:
    std::shared_ptr<mdk::Player> player_;
};
