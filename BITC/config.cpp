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
    if (setting->value("HaveRead").toString()=="1")return 1;//这时候已经初始化好了
    if(!(readSetting=new QSettings(":/resources/config.ini",QSettings::IniFormat)))
    {
        return 0;//读取失败
    }else {
        //开始读取设置
        setting->setValue("HaveRead",1);
        //支持中文
        setting->setIniCodec(QTextCodec::codecForName("utf-8"));
        //初始化行边颜色
        setting->setValue("LineColor","#EEEEEE");
        //qDebug()<<"set"<<setting->value("LineColor");
        //初始化字体
        setting->setValue("CodeFont","Consolas");
        //初始化字体大小
        setting->setValue("editorfontsize",12);
        //初始化color组
        readSetting->beginGroup("colorgroup1");
        setting->beginGroup("colorgroup1");
        qDebug()<<"readsetting"<<readSetting->value("expFunctioncolor");
        setting->setValue("LineColor",readSetting->value("LineColor"));
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
        setting->setValue("LineColor",readSetting->value("LineColor"));
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
        setting->setValue("LineColor",readSetting->value("LineColor"));
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
        ChangeCodeStyle(1);
        return 1;
    }//读取成功

}
void Config::ChangeCodeStyle(int flag){//改代码风格
    setting->setValue("styleflag",flag);//将风格换为flag
    QString *GroupName=new QString("colorgroup");
    QString *CodeStylebf=new QString();//就是换一个colorgroup
    CodeStylebf->setNum(flag);
    GroupName->append(CodeStylebf);
    GroupName->append('/');
    setting->setValue("LineColor",setting->value(*GroupName+"LineColor"));
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
