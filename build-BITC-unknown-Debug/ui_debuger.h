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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Debuger
{
public:
    QPushButton *EnterButton;
    QTextBrowser *Information;
    QPushButton *Continue;
    QLineEdit *DisplayLine;
    QPushButton *StepOut;
    QPushButton *StepInto;
    QLineEdit *BreakLine;
    QPushButton *DisplayButton;
    QPushButton *Stop;
    QLabel *label_5;
    QLabel *label_3;
    QPushButton *StepOver;
    QLabel *label;
    QLineEdit *EnterLine;
    QPushButton *BreakButton;
    QLabel *label_4;
    QTableWidget *DisplayView;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *NowLineNumber;
    QPushButton *Start;

    void setupUi(QWidget *Debuger)
    {
        if (Debuger->objectName().isEmpty())
            Debuger->setObjectName(QString::fromUtf8("Debuger"));
        Debuger->resize(799, 600);
        EnterButton = new QPushButton(Debuger);
        EnterButton->setObjectName(QString::fromUtf8("EnterButton"));
        EnterButton->setGeometry(QRect(680, 270, 112, 34));
        Information = new QTextBrowser(Debuger);
        Information->setObjectName(QString::fromUtf8("Information"));
        Information->setGeometry(QRect(10, 10, 781, 251));
        Continue = new QPushButton(Debuger);
        Continue->setObjectName(QString::fromUtf8("Continue"));
        Continue->setGeometry(QRect(660, 420, 131, 34));
        DisplayLine = new QLineEdit(Debuger);
        DisplayLine->setObjectName(QString::fromUtf8("DisplayLine"));
        DisplayLine->setGeometry(QRect(10, 560, 221, 31));
        StepOut = new QPushButton(Debuger);
        StepOut->setObjectName(QString::fromUtf8("StepOut"));
        StepOut->setGeometry(QRect(471, 420, 141, 34));
        StepInto = new QPushButton(Debuger);
        StepInto->setObjectName(QString::fromUtf8("StepInto"));
        StepInto->setGeometry(QRect(470, 380, 141, 34));
        BreakLine = new QLineEdit(Debuger);
        BreakLine->setObjectName(QString::fromUtf8("BreakLine"));
        BreakLine->setGeometry(QRect(600, 560, 111, 31));
        DisplayButton = new QPushButton(Debuger);
        DisplayButton->setObjectName(QString::fromUtf8("DisplayButton"));
        DisplayButton->setGeometry(QRect(240, 560, 161, 34));
        Stop = new QPushButton(Debuger);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setGeometry(QRect(650, 330, 141, 34));
        label_5 = new QLabel(Debuger);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 280, 81, 18));
        label_3 = new QLabel(Debuger);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 540, 141, 20));
        StepOver = new QPushButton(Debuger);
        StepOver->setObjectName(QString::fromUtf8("StepOver"));
        StepOver->setGeometry(QRect(660, 380, 131, 34));
        label = new QLabel(Debuger);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 330, 101, 18));
        EnterLine = new QLineEdit(Debuger);
        EnterLine->setObjectName(QString::fromUtf8("EnterLine"));
        EnterLine->setGeometry(QRect(100, 270, 561, 31));
        BreakButton = new QPushButton(Debuger);
        BreakButton->setObjectName(QString::fromUtf8("BreakButton"));
        BreakButton->setGeometry(QRect(711, 560, 81, 34));
        label_4 = new QLabel(Debuger);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(470, 540, 141, 18));
        DisplayView = new QTableWidget(Debuger);
        if (DisplayView->columnCount() < 2)
            DisplayView->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        DisplayView->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        DisplayView->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        DisplayView->setObjectName(QString::fromUtf8("DisplayView"));
        DisplayView->setGeometry(QRect(10, 350, 391, 181));
        DisplayView->setRowCount(0);
        DisplayView->setColumnCount(2);
        DisplayView->horizontalHeader()->setVisible(true);
        DisplayView->horizontalHeader()->setCascadingSectionResizes(false);
        DisplayView->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        DisplayView->horizontalHeader()->setStretchLastSection(true);
        DisplayView->verticalHeader()->setVisible(false);
        label_2 = new QLabel(Debuger);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(470, 570, 131, 18));
        label_6 = new QLabel(Debuger);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(470, 490, 91, 18));
        NowLineNumber = new QLabel(Debuger);
        NowLineNumber->setObjectName(QString::fromUtf8("NowLineNumber"));
        NowLineNumber->setGeometry(QRect(560, 490, 221, 18));
        Start = new QPushButton(Debuger);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setGeometry(QRect(470, 330, 151, 34));

        retranslateUi(Debuger);

        QMetaObject::connectSlotsByName(Debuger);
    } // setupUi

    void retranslateUi(QWidget *Debuger)
    {
        Debuger->setWindowTitle(QCoreApplication::translate("Debuger", "Form", nullptr));
        EnterButton->setText(QCoreApplication::translate("Debuger", "Enter", nullptr));
#if QT_CONFIG(shortcut)
        EnterButton->setShortcut(QCoreApplication::translate("Debuger", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        Continue->setText(QCoreApplication::translate("Debuger", "Continue", nullptr));
        DisplayLine->setText(QString());
        StepOut->setText(QCoreApplication::translate("Debuger", "StepOut", nullptr));
        StepInto->setText(QCoreApplication::translate("Debuger", "StepInto", nullptr));
        BreakLine->setText(QString());
        DisplayButton->setText(QCoreApplication::translate("Debuger", "\346\267\273\345\212\240\345\217\230\351\207\217/\350\241\250\350\276\276\345\274\217", nullptr));
        Stop->setText(QCoreApplication::translate("Debuger", "\345\201\234\346\255\242\350\260\203\350\257\225", nullptr));
        label_5->setText(QCoreApplication::translate("Debuger", "Commands", nullptr));
        label_3->setText(QCoreApplication::translate("Debuger", "\345\217\230\351\207\217/\350\241\250\350\276\276\345\274\217\346\267\273\345\212\240", nullptr));
        StepOver->setText(QCoreApplication::translate("Debuger", "StepOver", nullptr));
        label->setText(QCoreApplication::translate("Debuger", "\345\217\230\351\207\217/\350\241\250\350\276\276\345\274\217", nullptr));
        BreakButton->setText(QCoreApplication::translate("Debuger", "\350\256\276\347\275\256\346\226\255\347\202\271", nullptr));
        label_4->setText(QCoreApplication::translate("Debuger", "\346\226\255\347\202\271\350\256\276\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem = DisplayView->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Debuger", "\345\220\215\347\247\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = DisplayView->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Debuger", "\345\200\274", nullptr));
        label_2->setText(QCoreApplication::translate("Debuger", "\346\226\255\347\202\271\350\241\214\345\217\267/\345\205\266\344\273\226\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("Debuger", "\345\275\223\345\211\215\350\241\214\345\217\267\357\274\232", nullptr));
        NowLineNumber->setText(QCoreApplication::translate("Debuger", "-1", nullptr));
        Start->setText(QCoreApplication::translate("Debuger", "\345\274\200\345\247\213\350\260\203\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Debuger: public Ui_Debuger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGER_H
