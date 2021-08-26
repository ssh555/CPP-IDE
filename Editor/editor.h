#ifndef Editor_H
#define Editor_H
#include <QPlainTextEdit>
#include <QObject>

#include <QPaintEvent>
#include <QResizeEvent>
#include <QSize>
#include <QWidget>
#include <type.h>
#include <QSyntaxHighlighter>
//Editor类
//继承QPlainTextEdit
class LineNumberArea;

class Editor : public QPlainTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);
    void Set_Mode(editorMode mode);//设置编辑模式
    void Line_Number_Area_Paint_Event(QPaintEvent *event);//
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void SLOT_UpdateLineNumberAreaWidth(int newBlockCount);
    void SLOT_HighlightCurrentLine();
    void SLOT_UpdateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};


class LineNumberArea : public QWidget
{
public:
    LineNumberArea(Editor *editor) : QWidget(editor) {
        Editor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(Editor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        Editor->Line_Number_Area_Paint_Event(event);
    }

private:
    Editor *Editor;
};

#endif // Editor_H
