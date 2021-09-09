#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "toolbox.h"
#include <FileMgr.h>
#include <QCompleter>
#include "editor.h"
#include "searchwindow.h"

#include <QCloseEvent>
#include <QTimer>

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum TabTemp{
    Temporary = true,
    Permanent = false,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    //第二个参数为true表示当前窗口为临时窗口，临时打开文件共用一个窗口
    void AddTextEditToEditArea(QString filename,bool isTemp);

    static MainWindow* Instance()
    {
        if (m_pInstance == NULL)
        {
            m_pInstance = new MainWindow();
        }
        return m_pInstance;
    }

    ///获取UI的控件
    //获取tabWgtEditArea
    QTabWidget* GettabWgtEditArea();
    //获取tabWgtResArea
    QTabWidget* GettabWgtResArea();
    //获取menubar
    QMenuBar* Getmenubar();
    //获取gBoxFileMgr
    QDockWidget* GetgBoxFileMgr();
    //获取statusbarTips
    QStatusBar* GetstatusbarTips();
    //获取toolBar
    QToolBar* GettoolBar();
    //设置自动保存信号
    void SetAutoSave(bool b,int time = 1000*60*3);//默认三分钟保存一次
    //打开历史文件
    void OpenHistroyFile();
    //正在读入或写入文件内容时不会触发textchanged
    static bool isReadingOrWriting;

protected:
    void closeEvent(QCloseEvent *) override;

private:
    MainWindow(QWidget *parent = nullptr);
    //MainWindow& operator==(const MainWindow&){}
    ~MainWindow();
    QCompleter *completer = nullptr;
    Editor *completingTextEdit;
    //QGridLayout,用于放置editor及相关组件(搜索框)
    QGridLayout *editorLayout;
    //临时窗口，只有一个
    QWidget *TempWidget;
    SearchWindow *searchWindow=NULL;
    static MainWindow* m_pInstance;

    Ui::MainWindow *ui;
    QAbstractItemModel *modelFromFile(const QString& fileName);
    //当前操作中的Editor
    Editor *workingEditor=NULL;
    //ToolBox,实现显示文件夹的类，不用管
    ToolBox *tBoxFolderMgr;
    //当前编辑器正在操作的文件绝对路径 用GetCFileName获得文件名  用GetFolderName获得文件夹路径
    QString openingFileName;
    //记录已打开的文件
    QStringList *openedFileNames;


    //当窗口大小改变时，其他控件等也跟着改变大小，用来适应窗口大小
    //void resizeEvent(QResizeEvent* event);
    //往gBoxFileMgr添加文件夹，参数为文件名，内部需要重新实现
    void AddFolderToGBox(QString foldername);

    //键盘按下响应事件，添加快捷键
    void keyPressEvent(QKeyEvent  *event) override;
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

    //在editarea创建textedit
    QWidget* CreateEditText(QString filename);

    //在指定路径创建文件
    bool CreateFile(QString filename);

    //获取TAB页对应的文件路径
    QString GetTABFilePath(QWidget *TabPage,QString fileName);

    //临时TAB页转非临时TAB页
    void TempTabToPermTab();

    //是否自动保存
    bool isAutoSave = false;
    //自动保存计时器
    QTimer* autoSaveTimer = new QTimer;
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
    //打开文件夹信号
    void SIGNAL_OpenFolder();
    //保存文件信号
    void SIGNAL_SaveFile();
    //另存文件信号
    void SIGNAL_SaveAsFile();
    //关闭所有文件信号
    void SIGNAL_CloseAll();
    //撤销信号
    void SIGNAL_Revocate();
    //恢复信号
    void SIGNAL_Restore();
    //剪切信号
    void SIGNAL_Shear();
    //复制信号
    void SIGNAL_Copy();
    //粘贴信号
    void SIGNAL_Paste();
    //查询访问信号
    void SIGNAL_Search();
    //替换信号
    void SIGNAL_Replace();
    //保存打开的文件信号
    void SIGNAL_SaveOpenedFiles();
    //Debug信号
    void SIGNAL_Debug();
    //文件不存在信号
    void SIGNAL_NotExist();
    //不是C/C++文件信号
    void SIGNAL_NotCorCpp();
    //编译错误信号
    void SIGNAL_CompileError();
    //程序未编译信号
    void SIGNAL_NotCompiled();
    //自动保存信号，isAutoSave为true则开启自动保存
    void SIGNAL_AutoSave();
    //快速跳转信号
    void SIGNAL_Jump();
    //安装mingw
    void SIGNAL_AddMingw();
};
#endif // MAINWINDOW_H
