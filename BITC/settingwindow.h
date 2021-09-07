#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <uiinterface.h>
namespace Ui {
class SettingWindow;
}

class SettingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();
    void Init();
    QSettings *setting;
private slots:
    void on_CommitBtn_clicked();
    //先获取到interface,方便之后用

    void on_pushButton_clicked();

private:
    UIInterface *inf =UIInterface::Instance();
    Ui::SettingWindow *ui;
};

#endif // SETTINGWINDOW_H
