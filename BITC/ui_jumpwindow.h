/********************************************************************************
** Form generated from reading UI file 'jumpwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JUMPWINDOW_H
#define UI_JUMPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JumpWindow
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;

    void setupUi(QWidget *JumpWindow)
    {
        if (JumpWindow->objectName().isEmpty())
            JumpWindow->setObjectName(QString::fromUtf8("JumpWindow"));
        JumpWindow->resize(274, 54);
        label = new QLabel(JumpWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 20, 68, 15));
        lineEdit = new QLineEdit(JumpWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 20, 113, 21));
        label_2 = new QLabel(JumpWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(230, 20, 68, 15));

        retranslateUi(JumpWindow);

        QMetaObject::connectSlotsByName(JumpWindow);
    } // setupUi

    void retranslateUi(QWidget *JumpWindow)
    {
        JumpWindow->setWindowTitle(QCoreApplication::translate("JumpWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("JumpWindow", "\350\267\263\350\275\254\345\210\260", nullptr));
        label_2->setText(QCoreApplication::translate("JumpWindow", "\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JumpWindow: public Ui_JumpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JUMPWINDOW_H
