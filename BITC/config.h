#ifndef CONFIG_H
#define CONFIG_H

#include <QtGui>
#define ORGNAME  "FFFZZ" //小组名称 fight find fucking zu zhang

#define PROGNAME "BITEDITOR"
#define VERSION  "0.3"
class Config
{
public:
    QSettings *setting;
    QSettings *readSetting;

    void reread(int);
    int init();//初始化，成功返回1，失败返回0
    void printChild();//打印所有setting
    static Config * GetInstance()//获得COnfig实例
    {
        if (config_Instance == NULL)
        {
            config_Instance = new Config();
        }
        return config_Instance;
    }
    void ChangeCodeStyle(int flag);
public slots:

    void reconfig(int receiver) { emit reread(receiver);}
private:
    static Config * config_Instance;
    Config();
};

#endif // CONFIG_H
