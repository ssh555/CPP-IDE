QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

RC_ICONS = Logo.ico

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FileMgr.cpp \
    ToolBox.cpp \
    ToolPage.cpp \
    config.cpp \
    editor.cpp \
    filelabel.cpp \
    highlighter.cpp \
    jumpwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    searchwindow.cpp \
    settingwindow.cpp \
    toolboxchild.cpp \
    gcccheck.cpp \
    uiinterface.cpp \
    debuger.cpp

HEADERS += \
    FileMgr.h \
    ToolBox.h \
    ToolPage.h \
    config.h \
    editor.h \
    filelabel.h \
    highlighter.h \
    jumpwindow.h \
    mainwindow.h \
    searchwindow.h \
    settingwindow.h \
    toolboxchild.h \
    gcccheck.h \
    type.h \
    uiinterface.h \
    debuger.h

FORMS += \
    FileMgr.ui \
    ToolBox.ui \
    ToolPage.ui \
    jumpwindow.ui \
    mainwindow.ui \
    searchwindow.ui \
    settingwindow.ui \
    toolboxchild.ui \
    debuger.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    UIImages.qrc \
    img.qrc \
    qss.qrc
