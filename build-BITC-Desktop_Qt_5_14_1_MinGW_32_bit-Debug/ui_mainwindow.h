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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
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
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWgtEditArea;
    QWidget *tab_2;
    QGroupBox *gBoxFileMgr;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuSelect;
    QMenu *menuRun;
    QMenu *menuHelp;
    QStatusBar *statusbarTips;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionNewFile = new QAction(MainWindow);
        actionNewFile->setObjectName(QString::fromUtf8("actionNewFile"));
        actionOpenFile = new QAction(MainWindow);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        actionOpenFolder = new QAction(MainWindow);
        actionOpenFolder->setObjectName(QString::fromUtf8("actionOpenFolder"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionCloseAll = new QAction(MainWindow);
        actionCloseAll->setObjectName(QString::fromUtf8("actionCloseAll"));
        actionRevocate = new QAction(MainWindow);
        actionRevocate->setObjectName(QString::fromUtf8("actionRevocate"));
        actionRestore = new QAction(MainWindow);
        actionRestore->setObjectName(QString::fromUtf8("actionRestore"));
        actionShear = new QAction(MainWindow);
        actionShear->setObjectName(QString::fromUtf8("actionShear"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName(QString::fromUtf8("actionFind"));
        actionReplace = new QAction(MainWindow);
        actionReplace->setObjectName(QString::fromUtf8("actionReplace"));
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        actionCompile = new QAction(MainWindow);
        actionCompile->setObjectName(QString::fromUtf8("actionCompile"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        actionCompileRun = new QAction(MainWindow);
        actionCompileRun->setObjectName(QString::fromUtf8("actionCompileRun"));
        actionDebug = new QAction(MainWindow);
        actionDebug->setObjectName(QString::fromUtf8("actionDebug"));
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QString::fromUtf8("action_9"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWgtEditArea = new QTabWidget(centralwidget);
        tabWgtEditArea->setObjectName(QString::fromUtf8("tabWgtEditArea"));
        tabWgtEditArea->setTabsClosable(true);
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWgtEditArea->addTab(tab_2, QString());

        gridLayout->addWidget(tabWgtEditArea, 0, 1, 1, 1);

        gBoxFileMgr = new QGroupBox(centralwidget);
        gBoxFileMgr->setObjectName(QString::fromUtf8("gBoxFileMgr"));
        gBoxFileMgr->setMinimumSize(QSize(200, 530));

        gridLayout->addWidget(gBoxFileMgr, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
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
        MainWindow->setMenuBar(menubar);
        statusbarTips = new QStatusBar(MainWindow);
        statusbarTips->setObjectName(QString::fromUtf8("statusbarTips"));
        MainWindow->setStatusBar(statusbarTips);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuSelect->menuAction());
        menubar->addAction(menuRun->menuAction());
        menubar->addAction(menuHelp->menuAction());
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

        retranslateUi(MainWindow);

        tabWgtEditArea->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNewFile->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266    CTRL+N", nullptr));
        actionOpenFile->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266    CTRL+O", nullptr));
        actionOpenFolder->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266\345\244\271", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230           CTRL+S", nullptr));
        actionSaveAs->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272        CTRL+SHIFT+S", nullptr));
        actionCloseAll->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\346\211\200\346\234\211    CTRL+W", nullptr));
        actionRevocate->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200          CTRL+Z", nullptr));
        actionRestore->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215          CTRL+Y", nullptr));
        actionShear->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207          CTRL+X", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266          CTRL+C", nullptr));
        actionPaste->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264          CTRL+V", nullptr));
        actionFind->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276          CTRL+F", nullptr));
        actionReplace->setText(QCoreApplication::translate("MainWindow", "\346\233\277\346\215\242          CTRL+R", nullptr));
        action_7->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        actionCompile->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\257\221          CTRL+B", nullptr));
        actionRun->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214          CTRL+R", nullptr));
        actionCompileRun->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\257\221\350\277\220\350\241\214   CTRL+ALT+N", nullptr));
        actionDebug->setText(QCoreApplication::translate("MainWindow", "\350\260\203\350\257\225", nullptr));
        action_9->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        actionHelp->setText(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251\346\226\207\346\241\243", nullptr));
        tabWgtEditArea->setTabText(tabWgtEditArea->indexOf(tab_2), QCoreApplication::translate("MainWindow", "File1.txt", nullptr));
        gBoxFileMgr->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\347\256\241\347\220\206\345\231\250", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        menuSelect->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251", nullptr));
        menuRun->setTitle(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
