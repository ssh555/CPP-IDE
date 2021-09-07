#include "highlighter.h"
#include <QRegularExpression>
#include "config.h"
Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{

}

void Highlighter::Start_Highlight()
{
    HighlightingRule rule;
    QSettings *setting=new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());

    //颜色画笔
    QColor *b1=new QColor(setting->value("keywordColor").toString());
    //qDebug()<<setting->value("colorgroup1/keywordColor").toString();
    //关键字颜色
    //终归是蓝色好看

    keywordFormat.setForeground(*b1);
    keywordFormat.setFontWeight(QFont::Bold);
//    qDebug()<<"keywordFormat"<<setting->value("keywordColor").toString();
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b"  << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" <<"\\bdefine\\b"
                    << "\\bfloat\\b" << "\\bsizeof\\b" << "\\bint\\b"
                    << "\\blong\\b"  <<"\\bextern\\b"<<"\\bregister\\b"
                    << "\\bshort\\b"  << "\\bsigned\\b"
                     << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btypedef\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
    //额外函数关键字颜色
    QStringList expFunctionPatterns;
    expFunctionPatterns<<  "\\bauto\\b" << "\\bbreak\\b" << "\\bcase\\b"
                    << "\\bcontinue\\b" << "\\bdefault\\b" << "\\bdo\\b"
                    << "\\belse\\b"  << "\\bfor\\b"<<"[#]include"
                    << "\\bgoto\\b" << "\\bif\\b"
                    <<  "\\breturn\\b" << "\\bswitch\\b" << "\\bwhile\\b";

    //粉的
    b1=new QColor(setting->value("expFunctioncolor").toString());
    expFunctionFormat.setForeground(*b1);
    expFunctionFormat.setFontWeight(QFont::Bold);
    foreach (const QString &pattern, expFunctionPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = expFunctionFormat;
        highlightingRules.append(rule);
    }

    //类颜色
    QTextCharFormat classselfFormat;
    classselfFormat.setFontWeight(QFont::Bold);
    //玫红
    b1=new QColor(setting->value("classselfColor").toString());
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bclass\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);
    classFormat.setFontWeight(QFont::Bold);
    //玫红

    b1=new QColor(setting->value("classColor").toString());
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);
    //单行注释颜色

    //棕色
    b1=new QColor(setting->value("singleLineCommentColor").toString());
    singleLineCommentFormat.setForeground(*b1);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
    //多行注释颜色
    //浅棕色
    b1=new QColor(setting->value("multiLineCommentColor").toString());
    multiLineCommentFormat.setForeground(*b1);
    b1=new QColor(setting->value("quotationColor").toString());
    quotationFormat.setForeground(*b1);
    rule.pattern = QRegExp("\"[^\"]*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);
//    rule.pattern = QRegExp("([^)]*)");
//    rule.format = quotationFormat;
//    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    //函数颜色
    b1=new QColor(setting->value("functionColor").toString());
    functionFormat.setForeground(*b1);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);


    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}
void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);


    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                    + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}

