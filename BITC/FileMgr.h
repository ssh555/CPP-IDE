#ifndef FILEMGR_H
#define FILEMGR_H

#include <QWidget>

namespace Ui {
class FileMgr;
}

class FileMgr : public QWidget
{
    Q_OBJECT

public:
    explicit FileMgr(QWidget *parent = nullptr);
    ~FileMgr();

private:
    Ui::FileMgr *ui;
};

#endif // FILEMGR_H
