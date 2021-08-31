#include "editor.h"
#include <QtWidgets>
#include<QPlainTextEdit>
#include<QDebug>
Editor::Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    this->Init();
}
void Editor::Init()
{
    lineNumberArea = new LineNumberArea(this);
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(SLOT_UpdateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(SLOT_UpdateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(SLOT_HighlightCurrentLine()));
    //改了个可爱的字体
    this->setFont(QFont("Consolas",12));
    SLOT_UpdateLineNumberAreaWidth(0);
    int fontWidth = QFontMetrics(this->currentCharFormat().font()).averageCharWidth();
    this->setTabStopWidth( 3 * fontWidth );
    Set_Mode(BROWSE);

    QStringList list;
    list<< "\\bchar\\b"  << "\\bconst\\b"
        << "\\bdouble\\b" << "\\benum\\b" <<"\\bdefine\\b"
        << "\\bfloat\\b" << "\\bsizeof\\b" << "\\bint\\b"
        << "\\blong\\b"  <<"\\bextern\\b"<<"\\bregister\\b"
        << "\\bshort\\b"  << "\\bsigned\\b"
         << "\\bstatic\\b" << "\\bstruct\\b"
        << "\\btypedef\\b"
        << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
        << "\\bvoid\\b" << "\\bvolatile\\b"<<  "\\bauto\\b" << "\\bbreak\\b" << "\\bcase\\b"
        << "\\bcontinue\\b" << "\\bdefault\\b" << "\\bdo\\b"
        << "\\belse\\b"  << "\\bfor\\b"<<"[#]include"
        << "\\bgoto\\b" << "\\bif\\b"
        <<  "\\breturn\\b" << "\\bswitch\\b" << "\\bwhile\\b";


}
void Editor::setCompleter(QCompleter *completer)
{
//    if (c!=nullptr)
//        c->disconnect(this);

    c = completer;

//    if (!c)
//        return;

    c->setWidget(this);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(c, QOverload<const QString &>::of(&QCompleter::activated),
                     this, &Editor::insertCompletion);
}
//! [2]

//! [3]
QCompleter *Editor::completer() const
{
    return c;
}
//! [3]

//! [4]
void Editor::insertCompletion(const QString &completion)
{
    if (c->widget() != this)
        return;
    QTextCursor tc = textCursor();
    int extra = completion.length() - c->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}
//! [4]

//! [5]
QString Editor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}
//! [5]

//! [6]
void Editor::focusInEvent(QFocusEvent *e)
{
    if (c)
        c->setWidget(this);
    QPlainTextEdit::focusInEvent(e);
}
//! [6]

//! [7]
void Editor::keyPressEvent(QKeyEvent *e)
{
    if (c && c->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    const bool isShortcut = (e->modifiers().testFlag(Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
    if (!c || !isShortcut) // do not process the shortcut when we have a completer
        QPlainTextEdit::keyPressEvent(e);
//! [7]

//! [8]
    const bool ctrlOrShift = e->modifiers().testFlag(Qt::ControlModifier) ||
                             e->modifiers().testFlag(Qt::ShiftModifier);
    if (!c || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    const bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
                      || eow.contains(e->text().right(1)))) {
        c->popup()->hide();
        return;
    }

    if (completionPrefix != c->completionPrefix()) {
        c->setCompletionPrefix(completionPrefix);
        c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0)
                + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr); // popup it up!
}
Editor::Editor(QWidget *parent,QString foldername) : QPlainTextEdit(parent){
    FolderName = foldername;
    this->Init();
}/*
void Editor::insertCompletion(const QString& completion)
{
    if (c->widget() != this)
        return;
    QTextCursor tc = textCursor();

    qDebug()<<completion.length();
    qDebug()<<c->completionPrefix().length();
    int extra = completion.length()- c->completionPrefix().length();

    qDebug()<<extra;

#ifndef QT_NO_CURSOR

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    tc.select(QTextCursor::WordUnderCursor);
    qDebug()<<"selecte text: "+tc.selectedText ();
    tc.selectedText();

    tc.deleteChar();

    //tc.movePosition(QTextCursor::WordLeft);
    //tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion);

    tc = textCursor();

    setTextCursor(tc);

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
}*/


void Editor::Refresh_Text()
{

}
int Editor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void Editor::SLOT_UpdateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void Editor::SLOT_UpdateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        SLOT_UpdateLineNumberAreaWidth(0);
}

void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}
void Editor::SLOT_HighlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(242,238,227);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void Editor::Line_Number_Area_Paint_Event(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);


    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(-2, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}



void Editor::toggleComment()
{
    QTextCursor cursor = textCursor();

    {
        int end = document()->findBlock(cursor.selectionEnd()).blockNumber();

        cursor.beginEditBlock();

        for (int i = document()->findBlock(cursor.selectionStart()).blockNumber(); i <= end; i++) {
            QTextBlock block = document()->findBlockByNumber(i);

            cursor.setPosition(block.position());
            block.text()[0] == ';' ? cursor.deleteChar() : cursor.insertText(";");
        }

        cursor.endEditBlock();
    }
}

void Editor::Set_Mode(editorMode mode)
{
    if(mode == BROWSE)
    {
        this->setReadOnly(true);
        this->setStyleSheet("background:#f2f2f3;");
         SLOT_HighlightCurrentLine();
    }
    else if(mode == EDIT)
    {
        this->setReadOnly(false);
        this->setStyleSheet("background:#ffffff;");
         SLOT_HighlightCurrentLine();
    }
}
