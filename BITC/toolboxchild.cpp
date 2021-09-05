#include "toolboxchild.h"
#include "ui_toolboxchild.h"
#include "ToolPage.h"

ToolBoxChild::ToolBoxChild(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBoxChild),
    m_pContentVBoxLayout(nullptr)
{
    ui->setupUi(this);

    myParent = parent;

    //qDebug() << parent->width() << "    " << parent->height();
    //this->setGeometry(0,10,parent->width(),parent->height()-10);

    //    this->setMaximumSize(200,600);
    //    this->setMinimumSize(200,500);


    QWidget *widget = new QWidget(this);
    m_pContentVBoxLayout = new QVBoxLayout;
    m_pContentVBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_pContentVBoxLayout->setSpacing(2);

    QVBoxLayout *vBoxLayout = new QVBoxLayout(widget);
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->addLayout(m_pContentVBoxLayout);
    vBoxLayout->addStretch(1);
    ui->verticalLayout->addWidget(widget);
    //ui->scrollArea->setWidget(widget);
}

ToolBoxChild::~ToolBoxChild()
{
    delete ui;
}

void ToolBoxChild::addWidget(const QString &title, QWidget *widget)
{
    ToolPage *page = new ToolPage(this);
    page->addWidget(title, widget);

    m_pContentVBoxLayout->addWidget(page);

}
