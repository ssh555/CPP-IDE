#include "uiinterface.h"

UIInterface::UIInterface(QObject *parent) : QObject(parent)
{

}



//更改总窗口，下方的函数可在此函数中调用，即只调用这一个函数即可完成风格更改
void UIInterface::SetUIInteface(){

}

//更改 总的tabEditArear
void UIInterface::SetTabEditArea(){

}
//更改 总的tabResArear
void UIInterface::SetTabResArea(){

}
//更改 总的menuBar
void UIInterface::SetMenuBar(){

}
//更改 总的gBoxFileMgr
void UIInterface::SetGBoxFileMgr(){

}
//更改 总的toolBar
void UIInterface::SetToolBar(){

}
//更改 提示栏
void UIInterface::SetStatusBarTips(){

}

UIInterface* UIInterface::m_pInstance = NULL;
