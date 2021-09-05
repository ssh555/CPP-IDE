#ifndef Highlighter_H
#define Highlighter_H
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);
    void Start_Highlight();
protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;
    QTextCharFormat expFunctionFormat;//goto等内置函数颜色
    QTextCharFormat keywordFormat;//关键字颜色-i9*
    QTextCharFormat classFormat;//类颜色
    QTextCharFormat singleLineKey;
    QTextCharFormat singleLineValue;
    QTextCharFormat singleLineCommentFormat;//单行注释颜色
    QTextCharFormat multiLineCommentFormat;//多行注释颜色
    QTextCharFormat quotationFormat;//引用颜色
    QTextCharFormat functionFormat;//函数颜色(printf之类)
};
#endif // Highlighter_H
