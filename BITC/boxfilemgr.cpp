#include "boxfilemgr.h"

#include <QDockWidget>
#include <QResizeEvent>

BoxFileMgr::BoxFileMgr(QWidget *parent) : QDockWidget(parent)
{

}

void BoxFileMgr::resizeEvent(QResizeEvent* event)
{
    BoxFileMgr::resizeEvent(event);
    // Your code here
    tBoxFolderMgr->Size_Changed();
}

void BoxFileMgr::SetBoxFolderMgr(ToolBox *t){
    tBoxFolderMgr = t;
}

