/********************************************************************************
** Form generated from reading UI file 'debuger.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGER_H
#define UI_DEBUGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Debuger
{
public:
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *Display;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTableWidget *DisplayView;
    QHBoxLayout *horizontalLayout;
    QLineEdit *DisplayLine;
    QPushButton *DisplayButton;
    QVBoxLayout *Buttons;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Start;
    QPushButton *Stop;
    QPushButton *StepInto;
    QPushButton *StepOut;
    QPushButton *StepOver;
    QPushButton *Continue;

    void setupUi(QWidget *Debuger)
    {
        if (Debuger->objectName().isEmpty())
            Debuger->setObjectName(QString::fromUtf8("Debuger"));
        Debuger->resize(801, 301);
        horizontalLayout_4 = new QHBoxLayout(Debuger);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        Display = new QVBoxLayout();
        Display->setObjectName(QString::fromUtf8("Display"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(Debuger);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        DisplayView = new QTableWidget(Debuger);
        if (DisplayView->columnCount() < 2)
            DisplayView->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        DisplayView->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        DisplayView->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        DisplayView->setObjectName(QString::fromUtf8("DisplayView"));
        DisplayView->setRowCount(0);
        DisplayView->setColumnCount(2);
        DisplayView->horizontalHeader()->setVisible(true);
        DisplayView->horizontalHeader()->setCascadingSectionResizes(false);
        DisplayView->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        DisplayView->horizontalHeader()->setStretchLastSection(true);
        DisplayView->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(DisplayView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        DisplayLine = new QLineEdit(Debuger);
        DisplayLine->setObjectName(QString::fromUtf8("DisplayLine"));

        horizontalLayout->addWidget(DisplayLine);

        DisplayButton = new QPushButton(Debuger);
        DisplayButton->setObjectName(QString::fromUtf8("DisplayButton"));

        horizontalLayout->addWidget(DisplayButton);


        verticalLayout_2->addLayout(horizontalLayout);


        Display->addLayout(verticalLayout_2);


        horizontalLayout_4->addLayout(Display);

        Buttons = new QVBoxLayout();
        Buttons->setObjectName(QString::fromUtf8("Buttons"));
        Buttons->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        Start = new QPushButton(Debuger);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Consolas\";"));

        horizontalLayout_3->addWidget(Start);

        Stop = new QPushButton(Debuger);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Consolas\";"));

        horizontalLayout_3->addWidget(Stop);


        verticalLayout_5->addLayout(horizontalLayout_3);

        StepInto = new QPushButton(Debuger);
        StepInto->setObjectName(QString::fromUtf8("StepInto"));
        StepInto->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Consolas\";"));

        verticalLayout_5->addWidget(StepInto);

        StepOut = new QPushButton(Debuger);
        StepOut->setObjectName(QString::fromUtf8("StepOut"));
        StepOut->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Consolas\";"));

        verticalLayout_5->addWidget(StepOut);

        StepOver = new QPushButton(Debuger);
        StepOver->setObjectName(QString::fromUtf8("StepOver"));
        StepOver->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Consolas\";"));

        verticalLayout_5->addWidget(StepOver);

        Continue = new QPushButton(Debuger);
        Continue->setObjectName(QString::fromUtf8("Continue"));
        Continue->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Consolas\";"));

        verticalLayout_5->addWidget(Continue);


        Buttons->addLayout(verticalLayout_5);


        horizontalLayout_4->addLayout(Buttons);


        retranslateUi(Debuger);

        QMetaObject::connectSlotsByName(Debuger);
    } // setupUi

    void retranslateUi(QWidget *Debuger)
    {
        Debuger->setWindowTitle(QCoreApplication::translate("Debuger", "Form", nullptr));
        label->setText(QCoreApplication::translate("Debuger", "\345\217\230\351\207\217/\350\241\250\350\276\276\345\274\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem = DisplayView->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Debuger", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = DisplayView->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Debuger", "\345\200\274", nullptr));
        DisplayLine->setText(QString());
        DisplayButton->setText(QCoreApplication::translate("Debuger", "\346\267\273\345\212\240\345\217\230\351\207\217/\350\241\250\350\276\276\345\274\217", nullptr));
        Start->setText(QCoreApplication::translate("Debuger", "\345\274\200\345\247\213\350\260\203\350\257\225", nullptr));
        Stop->setText(QCoreApplication::translate("Debuger", "\345\201\234\346\255\242\350\260\203\350\257\225", nullptr));
        StepInto->setText(QCoreApplication::translate("Debuger", "StepInto", nullptr));
        StepOut->setText(QCoreApplication::translate("Debuger", "StepOut", nullptr));
        StepOver->setText(QCoreApplication::translate("Debuger", "StepOver", nullptr));
        Continue->setText(QCoreApplication::translate("Debuger", "Continue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Debuger: public Ui_Debuger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGER_H
