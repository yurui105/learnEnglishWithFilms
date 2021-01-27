#ifndef IMPORTFILES_H
#define IMPORTFILES_H

#include <QWidget>

namespace Ui {
class ImportFiles;
}

class ImportFiles : public QWidget
{
    Q_OBJECT

public:
    explicit ImportFiles(QWidget *parent = nullptr);
    ~ImportFiles();

private:
    Ui::ImportFiles *ui;
};

#endif // IMPORTFILES_H
