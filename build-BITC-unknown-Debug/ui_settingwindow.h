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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingWindow
{
public:
    QPushButton *CommitBtn;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QComboBox *comboBox_5;
    QComboBox *SytleBox;
    QLabel *label_3;
    QComboBox *comboBox;
    QLabel *label_5;
    QComboBox *comboBox_4;
    QLabel *label_6;
    QComboBox *comboBox_3;
    QPushButton *pushButton;

    void setupUi(QWidget *SettingWindow)
    {
        if (SettingWindow->objectName().isEmpty())
            SettingWindow->setObjectName(QString::fromUtf8("SettingWindow"));
        SettingWindow->resize(698, 349);
        CommitBtn = new QPushButton(SettingWindow);
        CommitBtn->setObjectName(QString::fromUtf8("CommitBtn"));
        CommitBtn->setGeometry(QRect(450, 300, 93, 28));
        gridLayoutWidget = new QWidget(SettingWindow);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(60, 70, 571, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        comboBox_2 = new QComboBox(gridLayoutWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 0, 3, 1, 1);

        comboBox_5 = new QComboBox(gridLayoutWidget);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));

        gridLayout->addWidget(comboBox_5, 2, 1, 1, 1);

        SytleBox = new QComboBox(gridLayoutWidget);
        SytleBox->addItem(QString());
        SytleBox->addItem(QString());
        SytleBox->addItem(QString());
        SytleBox->setObjectName(QString::fromUtf8("SytleBox"));

        gridLayout->addWidget(SytleBox, 0, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 2, 3, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        comboBox_4 = new QComboBox(gridLayoutWidget);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        gridLayout->addWidget(comboBox_4, 4, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 2, 1, 1);

        comboBox_3 = new QComboBox(gridLayoutWidget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        gridLayout->addWidget(comboBox_3, 4, 3, 1, 1);

        pushButton = new QPushButton(SettingWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(560, 300, 93, 28));

        retranslateUi(SettingWindow);

        QMetaObject::connectSlotsByName(SettingWindow);
    } // setupUi

    void retranslateUi(QWidget *SettingWindow)
    {
        SettingWindow->setWindowTitle(QCoreApplication::translate("SettingWindow", "Form", nullptr));
        CommitBtn->setText(QCoreApplication::translate("SettingWindow", "\347\241\256\345\256\232", nullptr));
        label->setText(QCoreApplication::translate("SettingWindow", "\344\270\273\351\242\230", nullptr));
        label_2->setText(QCoreApplication::translate("SettingWindow", "\345\255\227\344\275\223", nullptr));
        label_4->setText(QCoreApplication::translate("SettingWindow", "\347\274\226\350\276\221\345\231\250\350\203\214\346\231\257\351\242\234\350\211\262", nullptr));
        SytleBox->setItemText(0, QCoreApplication::translate("SettingWindow", "\345\214\227\347\220\206\351\243\216\346\240\274", nullptr));
        SytleBox->setItemText(1, QCoreApplication::translate("SettingWindow", "\345\260\221\345\245\263\351\243\216\346\240\274", nullptr));
        SytleBox->setItemText(2, QCoreApplication::translate("SettingWindow", "\347\233\264\347\224\267\351\243\216\346\240\274", nullptr));

        label_3->setText(QCoreApplication::translate("SettingWindow", "\345\255\227\344\275\223\345\244\247\345\260\217", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SettingWindow", "6", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SettingWindow", "7", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("SettingWindow", "8", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("SettingWindow", "9", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("SettingWindow", "10", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("SettingWindow", "11", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("SettingWindow", "12", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("SettingWindow", "14", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("SettingWindow", "16", nullptr));
        comboBox->setItemText(9, QCoreApplication::translate("SettingWindow", "18", nullptr));
        comboBox->setItemText(10, QCoreApplication::translate("SettingWindow", "20", nullptr));
        comboBox->setItemText(11, QCoreApplication::translate("SettingWindow", "23", nullptr));
        comboBox->setItemText(12, QCoreApplication::translate("SettingWindow", "26", nullptr));
        comboBox->setItemText(13, QCoreApplication::translate("SettingWindow", "29", nullptr));
        comboBox->setItemText(14, QCoreApplication::translate("SettingWindow", "32", nullptr));
        comboBox->setItemText(15, QCoreApplication::translate("SettingWindow", "36", nullptr));
        comboBox->setItemText(16, QCoreApplication::translate("SettingWindow", "40", nullptr));
        comboBox->setItemText(17, QCoreApplication::translate("SettingWindow", "44", nullptr));
        comboBox->setItemText(18, QCoreApplication::translate("SettingWindow", "48", nullptr));

        label_5->setText(QCoreApplication::translate("SettingWindow", "\346\230\257\345\220\246\350\207\252\345\212\250\344\277\235\345\255\230", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("SettingWindow", "\346\230\257", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("SettingWindow", "\345\220\246", nullptr));

        label_6->setText(QCoreApplication::translate("SettingWindow", "\350\207\252\345\212\250\344\277\235\345\255\230\346\227\266\351\227\264", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("SettingWindow", "\345\215\212\345\210\206\351\222\237", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("SettingWindow", "1\345\210\206\351\222\237", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("SettingWindow", "2\345\210\206\351\222\237", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("SettingWindow", "5\345\210\206\351\222\237", nullptr));
        comboBox_3->setItemText(4, QCoreApplication::translate("SettingWindow", "10\345\210\206\351\222\237", nullptr));
        comboBox_3->setItemText(5, QCoreApplication::translate("SettingWindow", "30\345\210\206\351\222\237", nullptr));

        pushButton->setText(QCoreApplication::translate("SettingWindow", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingWindow: public Ui_SettingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWINDOW_H
