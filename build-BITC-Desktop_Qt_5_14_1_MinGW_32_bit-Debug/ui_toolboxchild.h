/********************************************************************************
** Form generated from reading UI file 'toolboxchild.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLBOXCHILD_H
#define UI_TOOLBOXCHILD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolBoxChild
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *ToolBoxChild)
    {
        if (ToolBoxChild->objectName().isEmpty())
            ToolBoxChild->setObjectName(QString::fromUtf8("ToolBoxChild"));
        ToolBoxChild->resize(167, 16);
        verticalLayout = new QVBoxLayout(ToolBoxChild);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(16, 0, 0, 0);

        retranslateUi(ToolBoxChild);

        QMetaObject::connectSlotsByName(ToolBoxChild);
    } // setupUi

    void retranslateUi(QWidget *ToolBoxChild)
    {
        ToolBoxChild->setWindowTitle(QCoreApplication::translate("ToolBoxChild", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToolBoxChild: public Ui_ToolBoxChild {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLBOXCHILD_H
