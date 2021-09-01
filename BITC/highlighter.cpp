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
    QSettings *setting=Config::GetInstance()->setting;
    //颜色画笔
    QColor *b1=new QColor(setting->value("keywordColor").toString());
    //qDebug()<<setting->value("colorgroup1/keywordColor").toString();
    //关键字颜色
    //终归是蓝色好看

    keywordFormat.setForeground(*b1);
    keywordFormat.setFontWeight(QFont::Bold);

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
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    //函数颜色
    //蓝色!
    b1=new QColor(setting->value("functionColor").toString());
    functionFormat.setForeground(*b1);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
//    //数字

//    rule.pattern=QRegExp(R"((?<=\b|\s|^)(?i)(?:(?:(?:(?:(?:\d+(?:'\d+)*)?\.(?:\d+(?:'\d+)*)(?:e[+-]?(?:\d+(?:'\d+)*))?)|(?:(?:\d+(?:'\d+)*)\.(?:e[+-]?(?:\d+(?:'\d+)*))?)|(?:(?:\d+(?:'\d+)*)(?:e[+-]?(?:\d+(?:'\d+)*)))|(?:0x(?:[0-9a-f]+(?:'[0-9a-f]+)*)?\.(?:[0-9a-f]+(?:'[0-9a-f]+)*)(?:p[+-]?(?:\d+(?:'\d+)*)))|(?:0x(?:[0-9a-f]+(?:'[0-9a-f]+)*)\.?(?:p[+-]?(?:\d+(?:'\d+)*))))[lf]?)|(?:(?:(?:[1-9]\d*(?:'\d+)*)|(?:0[0-7]*(?:'[0-7]+)*)|(?:0x[0-9a-f]+(?:'[0-9a-f]+)*)|(?:0b[01]+(?:'[01]+)*))(?:u?l{0,2}|l{0,2}u?)))(?=\b|\s|$))");
//    classselfFormat.setFontWeight(QFont::Bold);
//    b1->setRgb(75,194,242);
//    functionFormat.setForeground(*b1);
//    rule.format=classselfFormat;
//    highlightingRules.append(rule);

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
