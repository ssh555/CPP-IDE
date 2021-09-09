#include "ToolPage.h"
#include "ui_ToolPage.h"

#include <QDebug>
#include <QFormLayout>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>

ToolPage::ToolPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolPage),
    m_bIsExpanded(true),
    m_pLabel(nullptr)
{
    ui->setupUi(this);

    ui->widgetContent->setAttribute(Qt::WA_StyledBackground);


    connect(ui->pushButtonFold, &QPushButton::clicked, this, &ToolPage::onPushButtonFoldClicked);
}

ToolPage::~ToolPage()
{
    delete ui;
}

void ToolPage::addWidget(const QString &title, QWidget *widget)
{
    ui->pushButtonFold->setText(title);
    collapse();
    ui->verticalLayoutContent->addWidget(widget);
}

void ToolPage::expand()
{
    ui->widgetContent->show();
    m_bIsExpanded = true;
    ui->pushButtonFold->setIcon(QIcon(":/img/down-arrow.png"));
}

void ToolPage::collapse()
{
    ui->widgetContent->hide();
    m_bIsExpanded = false;
    ui->pushButtonFold->setIcon(QIcon(":/img/right-arrow.png"));
}

void ToolPage::onPushButtonFoldClicked()
{
    if (m_bIsExpanded) {
        collapse();
    } else {
        expand();
    }
}
