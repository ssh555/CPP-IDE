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
    setting = new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    if (setting->value("HaveRead").toString()=="2")return 1;//这时候已经初始化好了
    if(!(readSetting=new QSettings(":/resources/config.ini",QSettings::IniFormat)))
    {
        return 0;//读取失败
    }else {
        //开始读取设置
        setting->setValue("HaveRead",2);
        //支持中文
        setting->setIniCodec(QTextCodec::codecForName("utf-8"));
        //初始化color组
        readSetting->beginGroup("colorgroup1");
        setting->beginGroup("colorgroup1");
        qDebug()<<"readsetting"<<readSetting->value("expFunctioncolor");
        setting->setValue("expFunctioncolor",readSetting->value("expFunctioncolor"));
        setting->setValue("keywordColor",readSetting->value("keywordColor"));
        setting->setValue("classselfColor",readSetting->value("classselfColor"));
        setting->setValue("classColor",readSetting->value("classColor"));
        setting->setValue("singleLineCommentColor",readSetting->value("singleLineCommentColor"));
        setting->setValue("multiLineCommentColor",readSetting->value("multiLineCommentColor"));
        setting->setValue("quotationColor",readSetting->value("quotationColor"));
        setting->setValue("functionColor",readSetting->value("functionColor"));
        setting->setValue("findFormatColor",readSetting->value("findFormatColor"));//查询替换颜色
        setting->endGroup();
        setting->sync();
        readSetting->endGroup();
        //初始化color组
        readSetting->beginGroup("colorgroup2");
        setting->beginGroup("colorgroup2");
        setting->setValue("expFunctioncolor",readSetting->value("expFunctioncolor"));
        setting->setValue("keywordColor",readSetting->value("keywordColor"));
        setting->setValue("classselfColor",readSetting->value("classselfColor"));
        setting->setValue("classColor",readSetting->value("classColor"));
        setting->setValue("singleLineCommentColor",readSetting->value("singleLineCommentColor"));
        setting->setValue("multiLineCommentColor",readSetting->value("multiLineCommentColor"));
        setting->setValue("quotationColor",readSetting->value("quotationColor"));
        setting->setValue("functionColor",readSetting->value("functionColor"));
        setting->setValue("findFormatColor",readSetting->value("findFormatColor"));//查询替换颜色
        setting->endGroup();
        setting->sync();
        readSetting->endGroup();
        //初始化color组
        readSetting->beginGroup("colorgroup3");
        setting->beginGroup("colorgroup3");
        setting->setValue("expFunctioncolor",readSetting->value("expFunctioncolor"));
        setting->setValue("keywordColor",readSetting->value("keywordColor"));
        setting->setValue("classselfColor",readSetting->value("classselfColor"));
        setting->setValue("classColor",readSetting->value("classColor"));
        setting->setValue("singleLineCommentColor",readSetting->value("singleLineCommentColor"));
        setting->setValue("multiLineCommentColor",readSetting->value("multiLineCommentColor"));
        setting->setValue("quotationColor",readSetting->value("quotationColor"));
        setting->setValue("functionColor",readSetting->value("functionColor"));
        setting->setValue("findFormatColor",readSetting->value("findFormatColor"));//查询替换颜色
        setting->sync();
        setting->endGroup();
        readSetting->endGroup();
        ChangeCodeStyle();
        return 1;
    }//读取成功

}
void Config::ChangeCodeStyle(){//改代码风格

    QString *GroupName=new QString("colorgroup");
    int CodeStyleNum=setting->value("codeStyle").toString().toUInt();

//    setting->setValue("codeStyle",(CodeStyleNum+1)%3);
//    setting->setValue("codeStyle",CodeStyleNum);
    QString *CodeStylebf=new QString();//就是换一个colorgroup
    CodeStylebf->setNum((CodeStyleNum+1)%3+1);
    GroupName->append(CodeStylebf);
    GroupName->append('/');
    setting->setValue("expFunctioncolor",setting->value(*GroupName+"expFunctioncolor"));
    setting->setValue("keywordColor",setting->value(*GroupName+"keywordColor"));
    setting->setValue("classselfColor",setting->value(*GroupName+"classselfColor"));
    setting->setValue("classColor",setting->value(*GroupName+"classColor"));
    setting->setValue("singleLineCommentColor",setting->value(*GroupName+"singleLineCommentColor"));
    setting->setValue("multiLineCommentColor",setting->value(*GroupName+"multiLineCommentColor"));
    setting->setValue("quotationColor",setting->value(*GroupName+"quotationColor"));
    setting->setValue("functionColor",setting->value(*GroupName+"functionColor"));
    setting->setValue("findFormatColor",setting->value(*GroupName+"findFormatColor"));//查询替换颜色
    setting->sync();
}
Config * Config::config_Instance = NULL;
