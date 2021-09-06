/********************************************************************************
** Form generated from reading UI file 'settingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWINDOW_H
#define UI_SETTINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingWindow
{
public:
    QComboBox *SytleBox;
    QLabel *label;
    QPushButton *CommitBtn;

    void setupUi(QWidget *SettingWindow)
    {
        if (SettingWindow->objectName().isEmpty())
            SettingWindow->setObjectName(QString::fromUtf8("SettingWindow"));
        SettingWindow->resize(630, 431);
        SytleBox = new QComboBox(SettingWindow);
        SytleBox->addItem(QString());
        SytleBox->addItem(QString());
        SytleBox->addItem(QString());
        SytleBox->setObjectName(QString::fromUtf8("SytleBox"));
        SytleBox->setGeometry(QRect(200, 120, 87, 22));
        label = new QLabel(SettingWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 120, 101, 16));
        CommitBtn = new QPushButton(SettingWindow);
        CommitBtn->setObjectName(QString::fromUtf8("CommitBtn"));
        CommitBtn->setGeometry(QRect(340, 340, 93, 28));

        retranslateUi(SettingWindow);

        QMetaObject::connectSlotsByName(SettingWindow);
    } // setupUi

    void retranslateUi(QWidget *SettingWindow)
    {
        SettingWindow->setWindowTitle(QCoreApplication::translate("SettingWindow", "Form", nullptr));
        SytleBox->setItemText(0, QCoreApplication::translate("SettingWindow", "\347\233\264\347\224\267\351\243\216\346\240\274", nullptr));
        SytleBox->setItemText(1, QCoreApplication::translate("SettingWindow", "\345\214\227\347\220\206\351\243\216\346\240\274", nullptr));
        SytleBox->setItemText(2, QCoreApplication::translate("SettingWindow", "\345\260\221\345\245\263\351\243\216\346\240\274", nullptr));

        label->setText(QCoreApplication::translate("SettingWindow", "\350\256\276\347\275\256\344\273\243\347\240\201\351\243\216\346\240\274", nullptr));
        CommitBtn->setText(QCoreApplication::translate("SettingWindow", "\346\217\220\344\272\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingWindow: public Ui_SettingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWINDOW_H
