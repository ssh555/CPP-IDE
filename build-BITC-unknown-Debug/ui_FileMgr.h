/********************************************************************************
** Form generated from reading UI file 'FileMgr.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEMGR_H
#define UI_FILEMGR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileMgr
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *FileMgr)
    {
        if (FileMgr->objectName().isEmpty())
            FileMgr->setObjectName(QString::fromUtf8("FileMgr"));
        FileMgr->resize(274, 460);
        verticalLayout_3 = new QVBoxLayout(FileMgr);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout_3->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);


        retranslateUi(FileMgr);

        QMetaObject::connectSlotsByName(FileMgr);
    } // setupUi

    void retranslateUi(QWidget *FileMgr)
    {
        FileMgr->setWindowTitle(QCoreApplication::translate("FileMgr", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileMgr: public Ui_FileMgr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEMGR_H
