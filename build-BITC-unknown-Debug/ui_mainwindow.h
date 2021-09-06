/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNewFile;
    QAction *actionOpenFile;
    QAction *actionOpenFolder;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionCloseAll;
    QAction *actionRevocate;
    QAction *actionRestore;
    QAction *actionShear;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionFind;
    QAction *actionReplace;
    QAction *action_7;
    QAction *actionCompile;
    QAction *actionRun;
    QAction *actionCompileRun;
    QAction *actionDebug;
    QAction *action_9;
    QAction *actionHelp;
    QAction *actioncodeStyle;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWgtEditArea;
    QWidget *tab_2;
    QTabWidget *tabWgtResArea;
    QWidget *tab;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *tab_3;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *CompileLog;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuSelect;
    QMenu *menuRun;
    QMenu *menuHelp;
    QMenu *menuSetting;
    QDockWidget *gBoxFileMgr;
    QWidget *dockWidgetContents;
    QStatusBar *statusbarTips;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(674, 505);
        actionNewFile = new QAction(MainWindow);
        actionNewFile->setObjectName(QString::fromUtf8("actionNewFile"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/UIImages/New.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewFile->setIcon(icon);
        actionOpenFile = new QAction(MainWindow);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/UIImages/OpenFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile->setIcon(icon1);
        actionOpenFolder = new QAction(MainWindow);
        actionOpenFolder->setObjectName(QString::fromUtf8("actionOpenFolder"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/UIImages/OpenFolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFolder->setIcon(icon2);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/UIImages/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/UIImages/SaveAs.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveAs->setIcon(icon4);
        actionCloseAll = new QAction(MainWindow);
        actionCloseAll->setObjectName(QString::fromUtf8("actionCloseAll"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/UIImages/CloseAllTab.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCloseAll->setIcon(icon5);
        actionRevocate = new QAction(MainWindow);
        actionRevocate->setObjectName(QString::fromUtf8("actionRevocate"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/UIImages/Restore.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRevocate->setIcon(icon6);
        actionRestore = new QAction(MainWindow);
        actionRestore->setObjectName(QString::fromUtf8("actionRestore"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/UIImages/Redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRestore->setIcon(icon7);
        actionShear = new QAction(MainWindow);
        actionShear->setObjectName(QString::fromUtf8("actionShear"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName(QString::fromUtf8("actionFind"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/resources/UIImages/Find.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFind->setIcon(icon8);
        actionReplace = new QAction(MainWindow);
        actionReplace->setObjectName(QString::fromUtf8("actionReplace"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/resources/UIImages/Replace.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReplace->setIcon(icon9);
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        actionCompile = new QAction(MainWindow);
        actionCompile->setObjectName(QString::fromUtf8("actionCompile"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/resources/UIImages/Compile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCompile->setIcon(icon10);
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/resources/UIImages/Run.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon11);
        actionCompileRun = new QAction(MainWindow);
        actionCompileRun->setObjectName(QString::fromUtf8("actionCompileRun"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/resources/UIImages/ComplieRun.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCompileRun->setIcon(icon12);
        actionDebug = new QAction(MainWindow);
        actionDebug->setObjectName(QString::fromUtf8("actionDebug"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/resources/UIImages/Debug.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDebug->setIcon(icon13);
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QString::fromUtf8("action_9"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actioncodeStyle = new QAction(MainWindow);
        actioncodeStyle->setObjectName(QString::fromUtf8("actioncodeStyle"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tabWgtEditArea = new QTabWidget(centralwidget);
        tabWgtEditArea->setObjectName(QString::fromUtf8("tabWgtEditArea"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWgtEditArea->sizePolicy().hasHeightForWidth());
        tabWgtEditArea->setSizePolicy(sizePolicy);
        tabWgtEditArea->setStyleSheet(QString::fromUtf8("font:"));
        tabWgtEditArea->setTabsClosable(true);
        tabWgtEditArea->setMovable(false);
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        QFont font;
        font.setItalic(false);
        tab_2->setFont(font);
        tabWgtEditArea->addTab(tab_2, QString());

        gridLayout->addWidget(tabWgtEditArea, 0, 0, 1, 1);

        tabWgtResArea = new QTabWidget(centralwidget);
        tabWgtResArea->setObjectName(QString::fromUtf8("tabWgtResArea"));
        sizePolicy.setHeightForWidth(tabWgtResArea->sizePolicy().hasHeightForWidth());
        tabWgtResArea->setSizePolicy(sizePolicy);
        tabWgtResArea->setMinimumSize(QSize(0, 200));
        tabWgtResArea->setMaximumSize(QSize(16777215, 300));
        tabWgtResArea->setMovable(true);
        tabWgtResArea->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget = new QWidget(tab);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-1, -1, 521, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWgtResArea->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWgtResArea->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_2 = new QVBoxLayout(tab_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        CompileLog = new QTextEdit(tab_4);
        CompileLog->setObjectName(QString::fromUtf8("CompileLog"));
        CompileLog->setFrameShape(QFrame::NoFrame);
        CompileLog->setUndoRedoEnabled(false);
        CompileLog->setReadOnly(true);

        verticalLayout_2->addWidget(CompileLog);

        tabWgtResArea->addTab(tab_4, QString());

        gridLayout->addWidget(tabWgtResArea, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 674, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuSelect = new QMenu(menubar);
        menuSelect->setObjectName(QString::fromUtf8("menuSelect"));
        menuRun = new QMenu(menubar);
        menuRun->setObjectName(QString::fromUtf8("menuRun"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuSetting = new QMenu(menubar);
        menuSetting->setObjectName(QString::fromUtf8("menuSetting"));
        MainWindow->setMenuBar(menubar);
        gBoxFileMgr = new QDockWidget(MainWindow);
        gBoxFileMgr->setObjectName(QString::fromUtf8("gBoxFileMgr"));
        gBoxFileMgr->setMinimumSize(QSize(150, 100));
        gBoxFileMgr->setMaximumSize(QSize(500, 524287));
        gBoxFileMgr->setAutoFillBackground(false);
        gBoxFileMgr->setStyleSheet(QString::fromUtf8(""));
        gBoxFileMgr->setFeatures(QDockWidget::DockWidgetMovable);
        gBoxFileMgr->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        dockWidgetContents->setStyleSheet(QString::fromUtf8(""));
        gBoxFileMgr->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, gBoxFileMgr);
        statusbarTips = new QStatusBar(MainWindow);
        statusbarTips->setObjectName(QString::fromUtf8("statusbarTips"));
        statusbarTips->setStyleSheet(QString::fromUtf8("border: 1px solid gray;"));
        statusbarTips->setSizeGripEnabled(false);
        MainWindow->setStatusBar(statusbarTips);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMovable(false);
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuSelect->menuAction());
        menubar->addAction(menuRun->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menubar->addAction(menuSetting->menuAction());
        menuFile->addAction(actionNewFile);
        menuFile->addAction(actionOpenFile);
        menuFile->addAction(actionOpenFolder);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSaveAs);
        menuFile->addSeparator();
        menuFile->addSeparator();
        menuFile->addAction(actionCloseAll);
        menuEdit->addAction(actionRevocate);
        menuEdit->addAction(actionRestore);
        menuEdit->addSeparator();
        menuEdit->addAction(actionShear);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionFind);
        menuEdit->addAction(actionReplace);
        menuEdit->addSeparator();
        menuSelect->addAction(action_7);
        menuRun->addAction(actionCompile);
        menuRun->addAction(actionRun);
        menuRun->addAction(actionCompileRun);
        menuRun->addSeparator();
        menuRun->addAction(actionDebug);
        menuRun->addAction(action_9);
        menuHelp->addAction(actionHelp);
        menuSetting->addAction(actioncodeStyle);
        toolBar->addAction(actionRevocate);
        toolBar->addAction(actionRestore);
        toolBar->addSeparator();
        toolBar->addAction(actionNewFile);
        toolBar->addAction(actionOpenFile);
        toolBar->addAction(actionOpenFolder);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSaveAs);
        toolBar->addSeparator();
        toolBar->addAction(actionCompile);
        toolBar->addAction(actionRun);
        toolBar->addAction(actionCompileRun);
        toolBar->addSeparator();
        toolBar->addAction(actionDebug);
        toolBar->addSeparator();
        toolBar->addAction(actionFind);
        toolBar->addAction(actionReplace);
        toolBar->addSeparator();
        toolBar->addAction(actionCloseAll);

        retranslateUi(MainWindow);

        tabWgtEditArea->setCurrentIndex(0);
        tabWgtResArea->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNewFile->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266    CTRL+N", nullptr));
        actionNewFile->setIconText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionNewFile->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpenFile->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266    CTRL+O", nullptr));
        actionOpenFile->setIconText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(tooltip)
        actionOpenFile->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpenFolder->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271 CTRL+ALT+O", nullptr));
        actionOpenFolder->setIconText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", nullptr));
#if QT_CONFIG(tooltip)
        actionOpenFolder->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230           CTRL+S", nullptr));
        actionSave->setIconText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#if QT_CONFIG(tooltip)
        actionSave->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSaveAs->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272        CTRL+SHIFT+S", nullptr));
        actionSaveAs->setIconText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", nullptr));
#if QT_CONFIG(tooltip)
        actionSaveAs->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCloseAll->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\346\211\200\346\234\211    CTRL+W", nullptr));
        actionCloseAll->setIconText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\346\211\200\346\234\211", nullptr));
#if QT_CONFIG(tooltip)
        actionCloseAll->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\346\211\200\346\234\211", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRevocate->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200          CTRL+Z", nullptr));
        actionRevocate->setIconText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
#if QT_CONFIG(tooltip)
        actionRevocate->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionRevocate->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        actionRestore->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215          CTRL+Y", nullptr));
        actionRestore->setIconText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215", nullptr));
#if QT_CONFIG(tooltip)
        actionRestore->setToolTip(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215 ", nullptr));
#endif // QT_CONFIG(tooltip)
        actionShear->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207          CTRL+X", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266          CTRL+C", nullptr));
        actionPaste->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264          CTRL+V", nullptr));
        actionFind->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276          CTRL+F", nullptr));
        actionFind->setIconText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
#if QT_CONFIG(tooltip)
        actionFind->setToolTip(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
#endif // QT_CONFIG(tooltip)
        actionReplace->setText(QCoreApplication::translate("MainWindow", "\346\233\277\346\215\242          CTRL+SHIFT+F", nullptr));
        actionReplace->setIconText(QCoreApplication::translate("MainWindow", "\346\233\277\346\215\242", nullptr));
#if QT_CONFIG(tooltip)
        actionReplace->setToolTip(QCoreApplication::translate("MainWindow", "\346\233\277\346\215\242", nullptr));
#endif // QT_CONFIG(tooltip)
        action_7->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        actionCompile->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\257\221          CTRL+B", nullptr));
        actionCompile->setIconText(QCoreApplication::translate("MainWindow", "\347\274\226\350\257\221", nullptr));
#if QT_CONFIG(tooltip)
        actionCompile->setToolTip(QCoreApplication::translate("MainWindow", "\347\274\226\350\257\221", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRun->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214          CTRL+R", nullptr));
        actionRun->setIconText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
#if QT_CONFIG(tooltip)
        actionRun->setToolTip(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCompileRun->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\257\221\350\277\220\350\241\214   CTRL+ALT+N", nullptr));
        actionCompileRun->setIconText(QCoreApplication::translate("MainWindow", "\347\274\226\350\257\221\350\277\220\350\241\214", nullptr));
#if QT_CONFIG(tooltip)
        actionCompileRun->setToolTip(QCoreApplication::translate("MainWindow", "\347\274\226\350\257\221\350\277\220\350\241\214", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDebug->setText(QCoreApplication::translate("MainWindow", "\350\260\203\350\257\225", nullptr));
        action_9->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251\346\226\207\346\241\243", nullptr));
        actioncodeStyle->setText(QCoreApplication::translate("MainWindow", "\344\273\243\347\240\201\351\243\216\346\240\274", nullptr));
        tabWgtEditArea->setTabText(tabWgtEditArea->indexOf(tab_2), QCoreApplication::translate("MainWindow", "File1.txt", nullptr));
        tabWgtResArea->setTabText(tabWgtResArea->indexOf(tab), QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276", nullptr));
        tabWgtResArea->setTabText(tabWgtResArea->indexOf(tab_3), QCoreApplication::translate("MainWindow", " \350\260\203\350\257\225", nullptr));
        tabWgtResArea->setTabText(tabWgtResArea->indexOf(tab_4), QCoreApplication::translate("MainWindow", "\347\274\226\350\257\221\346\227\245\345\277\227", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        menuSelect->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251", nullptr));
        menuRun->setTitle(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        menuSetting->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        gBoxFileMgr->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\265\204\346\272\220\347\256\241\347\220\206\345\231\250", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
