#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "toolbox.h"
#include <FileMgr.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    //ToolBox,实现显示文件夹的类，不用管
    ToolBox *tBoxFolderMgr;
    //当前编辑器正在操作的文件绝对路径 用GetCFileName获得文件名  用GetFolderName获得文件夹路径
    QString openingFileName;

    //当窗口大小改变时，其他控件等也跟着改变大小，用来适应窗口大小
    //void resizeEvent(QResizeEvent* event);
    //往gBoxFileMgr添加文件夹，参数为文件名，内部需要重新实现
    void AddFolderToGBox(QString foldername);
    //往EditArea添加TextEdit
    void AddTextEditToEditArea(QString filename);
    //键盘按下响应事件，添加快捷键
    void keyPressEvent(QKeyEvent  *event);
    //编译C文件
    void CompileC(QString filename);
    //运行C文件
    void RunC(QString filename);
    //获取C文件绝对路径的文件名
    QString GetCFileName(QString filename);
    //获取C文件绝对路径的文件夹路径 不包括最后的/
    QString GetCFolderName(QString filename);

    /*需要初始化调用的函数*/
    //实现菜单栏的功能
    void Func_MenuBar();

    //在指定路径创建文件
    bool CreateFile(QString filename);

    /*信号*/
signals:
    //编译运行信号
    void SIGNAL_CompileRun();
    //编译信号
    void SIGNAL_Compile();
    //运行信号
    void SIGNAL_Run();
    //新建文件信号
    void SIGNAL_CreateNewFile();
    //打开文件信号
    void SIGNAL_OpenFile();
    //保存文件信号
    void SIGNAL_SaveFile();
    //另存文件信号
    void SIGNAL_SaveAsFile();
    //关闭所有文件信号
    void SIGNAL_CloseAll();

};
#endif // MAINWINDOW_H
