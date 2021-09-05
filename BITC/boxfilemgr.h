#ifndef BOXFILEMGR_H
#define BOXFILEMGR_H

#include <QDockWidget>

#include <toolbox.h>

class BoxFileMgr : public QDockWidget
{
    Q_OBJECT
public:
    explicit BoxFileMgr(QWidget *parent = nullptr);

    void SetBoxFolderMgr(ToolBox *t);

protected:
    //当窗口大小改变时，其他控件等也跟着改变大小，用来适应窗口大小
    void resizeEvent(QResizeEvent* event);

private:
    ToolBox *tBoxFolderMgr;

signals:

};

#endif // BOXFILEMGR_H
