#include "uiinterface.h"
#include <QSettings>
#include <QApplication>
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
//更改字体
void UIInterface::SLOT_ChangeCodeFont(bool flag){
    int num=tabEditArea->count();
    QSettings *setting=new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    int fontsize=setting->value("editorfontsize").toUInt();
    if((fontsize>50 and flag) or (fontsize<6 and !flag))return;
    if(flag){//增加
        fontsize++;
    }else{//降低
        fontsize--;
    }
    for(int i=0;i<num;i++){
        Editor *e=(Editor*)tabEditArea->widget(i);
        e->setFont(QFont("Consolas",fontsize));
    }
    setting->setValue("editorfontsize",fontsize);
    setting->sync();//防止操作过快
}

UIInterface* UIInterface::m_pInstance = NULL;
