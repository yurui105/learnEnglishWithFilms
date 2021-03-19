#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>
#include <QObject>

class MessageBox : public QMessageBox
{
    Q_OBJECT
public:
    explicit MessageBox();
};

#endif // MESSAGEBOX_H
