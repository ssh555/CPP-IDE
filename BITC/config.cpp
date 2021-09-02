#include "config.h"

Config::Config()
{
    this->init();
}
void Config::printChild()
{
    QStringList keys = setting->allKeys();
    for (int i=0;i<keys.length();i++){
        qDebug()<<keys.at(i);
    }
}

int Config::init()
{
    if(!(setting=new QSettings(":/resources/config.ini",QSettings::IniFormat)))
    {
        return 0;//读取失败
    }else {
        //开始初始化设置
        //支持中文
        setting->setIniCodec(QTextCodec::codecForName("utf-8"));
        //初始化color组
        setting->setValue("expFunctioncolor",setting->value("colorgroup1/expFunctioncolor"));
        setting->setValue("keywordColor",setting->value("colorgroup1/keywordColor"));
        setting->setValue("classselfColor",setting->value("colorgroup1/classselfColor"));
        setting->setValue("classColor",setting->value("colorgroup1/classColor"));
        setting->setValue("singleLineCommentColor",setting->value("colorgroup1/singleLineCommentColor"));
        setting->setValue("multiLineCommentColor",setting->value("colorgroup1/multiLineCommentColor"));
        setting->setValue("quotationColor",setting->value("colorgroup1/quotationColor"));
        setting->setValue("functionColor",setting->value("colorgroup1/functionColor"));
        setting->setValue("findFormatColor",setting->value("colorgroup1/findFormatColor"));//查询替换颜色
        setting->sync();
        return 1;
    }//读取成功

}
Config * Config::config_Instance = NULL;
