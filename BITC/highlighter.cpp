#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    //颜色画笔
    QColor *b1=new QColor();
    //关键字颜色
    //粉红马卡龙
    b1->setRgb(242,99,126);
    keywordFormat.setForeground(*b1);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfloat\\b" << "\\bsizeof\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
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
                    << "\\belse\\b" << "\\bextern\\b" << "\\bfor\\b"
                    << "\\bgoto\\b" << "\\bif\\b" << "\\bregister\\b"
                    <<  "\\breturn\\b" << "\\bswitch\\b" << "\\bwhile\\b";

    //黑色
    b1->setRgb(0,0,0);
    expFunctionFormat.setForeground(*b1);
    expFunctionFormat.setFontWeight(QFont::Bold);
    foreach (const QString &pattern, expFunctionPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = expFunctionFormat;
        highlightingRules.append(rule);
    }

    //类颜色
    classFormat.setFontWeight(QFont::Bold);
    //玫红
    b1->setRgb(166,51,72);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);
    //单行注释颜色

    //棕色
    b1->setRgb(153,191,177);
    singleLineCommentFormat.setForeground(*b1);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
    //多行注释颜色
    //浅棕色
    b1->setRgb(222,156,126);
    multiLineCommentFormat.setForeground(*b1);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    //函数颜色
    //蓝色!
    b1->setRgb(75,194,242);
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
