#ifndef TOOLBOXCHILD_H
#define TOOLBOXCHILD_H

#include <QObject>
#include <QWidget>

namespace Ui {
class ToolBoxChild;
}

class QVBoxLayout;
class ToolBoxChild : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBoxChild(QWidget *parent = nullptr);
    ~ToolBoxChild();

    void addWidget(const QString &title, QWidget *widget);

    //void Size_Changed();

private:
    Ui::ToolBoxChild *ui;
    QWidget *myParent;
    QVBoxLayout *m_pContentVBoxLayout;

signals:

};

#endif // TOOLBOXCHILD_H
