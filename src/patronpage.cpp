#include "patronpage.h"
#include "ui_patronpage.h"

PatronPage::PatronPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatronPage)
{
    ui->setupUi(this);

    //隐藏菜单栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    //绑定确认按钮关闭窗口
    QObject::connect(ui->okButton,&QPushButton::clicked,this,&QWidget::close);

    //设置支付二维码
    QImage wechat,alipay;
    wechat.load("://patron/image/patron/wechat.png");
    alipay.load("://patron/image/patron/alipay.jpg");
    QPixmap wechatPix = QPixmap::fromImage(wechat);
    QPixmap alipayPix = QPixmap::fromImage(alipay);
    QPixmap wechatFitpixmap = wechatPix.scaled(ui->wechat->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QPixmap alipayFitpixmap = alipayPix.scaled(ui->alipay->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    ui->alipay->setPixmap(alipayFitpixmap);
    ui->wechat->setPixmap(wechatFitpixmap);
}

PatronPage::~PatronPage()
{
    delete ui;
}
