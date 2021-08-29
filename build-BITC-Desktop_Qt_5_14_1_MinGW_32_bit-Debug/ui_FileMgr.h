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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileMgr
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *btnFile1;
    QPushButton *btnFile2;
    QPushButton *btnFile3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *FileMgr)
    {
        if (FileMgr->objectName().isEmpty())
            FileMgr->setObjectName(QString::fromUtf8("FileMgr"));
        FileMgr->resize(274, 460);
        verticalLayout = new QVBoxLayout(FileMgr);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnFile1 = new QPushButton(FileMgr);
        btnFile1->setObjectName(QString::fromUtf8("btnFile1"));

        verticalLayout->addWidget(btnFile1);

        btnFile2 = new QPushButton(FileMgr);
        btnFile2->setObjectName(QString::fromUtf8("btnFile2"));

        verticalLayout->addWidget(btnFile2);

        btnFile3 = new QPushButton(FileMgr);
        btnFile3->setObjectName(QString::fromUtf8("btnFile3"));

        verticalLayout->addWidget(btnFile3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(FileMgr);

        QMetaObject::connectSlotsByName(FileMgr);
    } // setupUi

    void retranslateUi(QWidget *FileMgr)
    {
        FileMgr->setWindowTitle(QCoreApplication::translate("FileMgr", "Form", nullptr));
        btnFile1->setText(QCoreApplication::translate("FileMgr", "File1.txt", nullptr));
        btnFile2->setText(QCoreApplication::translate("FileMgr", "File2.txt", nullptr));
        btnFile3->setText(QCoreApplication::translate("FileMgr", "File3.txt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileMgr: public Ui_FileMgr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEMGR_H
