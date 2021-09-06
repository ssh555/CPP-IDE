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
#include <QCompleter>
#include "highlighter.h"
//Editor类
//继承QPlainTextEdit
class LineNumberArea;

class Editor : public QPlainTextEdit
{
    Q_OBJECT

public:
    QTextCharFormat colorFormat;//查询颜色
    void ChangeCodeStyle();
    void FoldCurrent();
    Highlighter *highlighter;//高亮器
    QCompleter *c = nullptr;
    void setCompleter(QCompleter *c);
    QCompleter *completer() const;
    Editor(QWidget *parent = 0);
    Editor(QWidget *parent,QString foldername);
    void toggleComment();
    void performCompletion();
    void Init();//初始化
    void Set_Mode(editorMode mode);//设置编辑模式
    void Line_Number_Area_Paint_Event(QPaintEvent *event);//
    int lineNumberAreaWidth();
    QString FolderName;//保存当前页的文件的文件夹绝对路径
    bool isChanged;
    QVector<qint32> GetBreakPoints();//获取断点堆
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    int CountLeftKuohao(QTextBlock block);//判断括号
    //字符组状态
    enum BlockState {
        End         = 1,     // 00000001
        Begin       = 2,     // 00000010
        String      = 4,     // 00000100
        Comment     = 8,     // 00001000
        Debug       = 8,     // 00001000
        Nested      = 16,    // 00010000
        Folded      = 32,    // 00100000
        Error       = 64,    // 01000000
        Rehighlight = 128,   // 10000000
        //Bookmark    = 256, // 100000000
        Empty       = -1     // 1111....
    };
    const static int StateShift = 8;//切换模式
    bool FindAllState=false;//用来观测有没有进行全局查看
public :signals:
    void SIGNAL_ChangeCodeStyle();
    void SIGNAL_ChangeFont(bool flag);
protected:
    void wheelEvent(QWheelEvent *e) override;
    void FoldUnfold(QTextBlock &block);
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void Refresh_Text();
    void keyPressEvent(QKeyEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;
    void autoIndent(bool temp);
    void addBraceRight();

public slots:
    bool SLOT_FindKeywords(QString keyword);
    bool SLOT_FindWhole(QString keyword);
    bool SLOT_FindPrivious(QString keyword);
    bool SLOT_ReplaceKeywords(QString keyword,QString replaceword);
    void SLOT_ReplaceWhole(QString keyword,QString replaceword);
    bool SLOT_ReplacePrivious(QString keyword,QString replaceword);
    void SLOT_SearchEnd();//搜索结束
    void FoldUnfoldAll(bool folding);//用于代码折叠

    void SLOT_ChangeLineNum(int num);

private slots:

    void insertCompletion(const QString &completion);
    void SLOT_UpdateLineNumberAreaWidth(int newBlockCount);
    void SLOT_HighlightCurrentLine();
    void SLOT_UpdateLineNumberArea(const QRect &, int);

private:
    QString textUnderCursor() const;

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
