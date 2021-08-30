#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>

namespace Ui {
class ToolBox;
}

class QVBoxLayout;
class ToolBox : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBox(QWidget *parent = nullptr);
    ~ToolBox();

    void addWidget(const QString &title, QWidget *widget);

    //void Size_Changed();

private:
    Ui::ToolBox *ui;
    QWidget *myParent;
    QVBoxLayout *m_pContentVBoxLayout;
};

#endif // TOOLBOX_H
