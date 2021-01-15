#ifndef PATRONPAGE_H
#define PATRONPAGE_H

#include <QWidget>
#include<QImage>
#include<QPixmap>
#include<QPushButton>

namespace Ui {
class PatronPage;
}

class PatronPage : public QWidget
{
    Q_OBJECT

public:
    explicit PatronPage(QWidget *parent = nullptr);
    ~PatronPage();

private:
    Ui::PatronPage *ui;
};

#endif // PATRONPAGE_H
