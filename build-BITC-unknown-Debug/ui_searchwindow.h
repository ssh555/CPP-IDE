/********************************************************************************
** Form generated from reading UI file 'searchwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWINDOW_H
#define UI_SEARCHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchWindow
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnFindPrivious;
    QPushButton *btnFindWhole;
    QPushButton *btnFindNext;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnFind;
    QPushButton *btnReplace;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QWidget *SearchWindow)
    {
        if (SearchWindow->objectName().isEmpty())
            SearchWindow->setObjectName(QString::fromUtf8("SearchWindow"));
        SearchWindow->resize(682, 152);
        gridLayout = new QGridLayout(SearchWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        btnFindPrivious = new QPushButton(SearchWindow);
        btnFindPrivious->setObjectName(QString::fromUtf8("btnFindPrivious"));

        verticalLayout_2->addWidget(btnFindPrivious);

        btnFindWhole = new QPushButton(SearchWindow);
        btnFindWhole->setObjectName(QString::fromUtf8("btnFindWhole"));

        verticalLayout_2->addWidget(btnFindWhole);

        btnFindNext = new QPushButton(SearchWindow);
        btnFindNext->setObjectName(QString::fromUtf8("btnFindNext"));

        verticalLayout_2->addWidget(btnFindNext);


        gridLayout->addLayout(verticalLayout_2, 1, 1, 2, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnFind = new QPushButton(SearchWindow);
        btnFind->setObjectName(QString::fromUtf8("btnFind"));

        horizontalLayout_2->addWidget(btnFind);

        btnReplace = new QPushButton(SearchWindow);
        btnReplace->setObjectName(QString::fromUtf8("btnReplace"));

        horizontalLayout_2->addWidget(btnReplace);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SearchWindow);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(SearchWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 1, 0, 2, 1);


        retranslateUi(SearchWindow);

        QMetaObject::connectSlotsByName(SearchWindow);
    } // setupUi

    void retranslateUi(QWidget *SearchWindow)
    {
        SearchWindow->setWindowTitle(QCoreApplication::translate("SearchWindow", "Form", nullptr));
        btnFindPrivious->setText(QCoreApplication::translate("SearchWindow", "\344\270\212\344\270\200\344\270\252", nullptr));
        btnFindWhole->setText(QCoreApplication::translate("SearchWindow", "\344\273\216\345\244\264\346\237\245\346\211\276", nullptr));
        btnFindNext->setText(QCoreApplication::translate("SearchWindow", "\344\270\213\344\270\200\344\270\252", nullptr));
        btnFind->setText(QCoreApplication::translate("SearchWindow", "\346\237\245\346\211\276", nullptr));
        btnReplace->setText(QCoreApplication::translate("SearchWindow", "\346\233\277\346\215\242", nullptr));
        label->setText(QCoreApplication::translate("SearchWindow", "\346\237\245\346\211\276\345\206\205\345\256\271:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchWindow: public Ui_SearchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWINDOW_H
