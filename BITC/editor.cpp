#include "editor.h"
#include <QtWidgets>
#include<QPlainTextEdit>
#include<QDebug>
#include "config.h"
#include "highlighter.h"
#include "config.h"
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
    this->setTabStopDistance( 3 * fontWidth );
    Set_Mode(BROWSE);
    //设置高亮
    highlighter = new Highlighter(this->document());
    highlighter->Start_Highlight();


}

void Editor::SLOT_ReplaceWhole(QString findword,QString replaceword)
{
    QTextCursor cursor = textCursor();

    cursor.setPosition(0, QTextCursor::MoveAnchor);
    setTextCursor(cursor);

    while (SLOT_ReplaceKeywords(findword, replaceword));
}
QVector<qint32> Editor::GetBreakPoints()
{
    QVector<qint32> *breakpoints=new QVector<qint32>;
    QTextBlock b=document()->firstBlock();
    while(b.next().isValid()){
        if(b.userState()&Debug){
            breakpoints->append(b.lineCount());
        qDebug()<<(b.lineCount());
        }
        b=b.next();
    }
    return *breakpoints;
}
bool Editor::SLOT_ReplaceKeywords(QString findword,QString replaceword)//替换下一个
{
    QTextCursor cursor = textCursor();

    if (!cursor.hasSelection())
        return SLOT_FindKeywords(findword);

    //int pos = textCursor().position() - textCursor().selectedText().length();

    cursor.beginEditBlock();
    cursor.insertText(replaceword);
    cursor.endEditBlock();


    return true;
}
bool Editor::SLOT_ReplacePrivious(QString findword,QString replaceword)//替换前一个
{
    QTextCursor cursor = textCursor();

    if (!cursor.hasSelection())
        return SLOT_FindPrivious(findword);

    int pos = textCursor().position() - textCursor().selectedText().length();

    cursor.beginEditBlock();
    cursor.insertText(replaceword);
    cursor.endEditBlock();

    cursor.setPosition(pos, QTextCursor::MoveAnchor);
    setTextCursor(cursor);
    return true;
}
bool Editor::SLOT_FindWhole(QString keyword)//寻找关键字
{
    this ->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);
    QTextCursor cursor = this->textCursor();
    cursor = document()->find(keyword, cursor);
    if(cursor.isNull()){
        return false;
    }
    setTextCursor(cursor);
    return true;
}
void Editor::SLOT_SearchEnd()
{
    //查询结束,把之前换的颜色换回去
    //    if(FindAllState==true){
    //            QTextDocument *document = this->document();
    //            // undo previous change (if any)
    //            document->undo();
    //    }

}
void Editor::FoldUnfoldAll(bool folding)//折叠代码
{
    QTextBlock block = document()->firstBlock();
    int blockcount=0;
    do {
        int state = block.userState();
        blockcount++;
        //如果该block可见、错误、嵌套、已经折叠且folding为true、未折叠且folding为false，就跳过这个block
        if (!block.isVisible() || state & Error || state & Nested ||
            (state & Folded && folding) || (!(state & Folded) && !folding))
            continue;
        //反过来就不可见且正确并且未嵌套，同时折叠情况和folding有且仅有一个为true
        //进行FoldUnfold
        FoldUnfold(block);
    } while ((block = block.next()).isValid());

    ensureCursorVisible();

}

void Editor::ChangeCodeStyle(){
    Config::GetInstance()->ChangeCodeStyle();
    highlighter = new Highlighter(this->document());
    highlighter->Start_Highlight();



}

void Editor::FoldUnfold(QTextBlock &block)
{
    int state = block.userState();
    //如果该代码块错误或已经到结尾或document的最后一个代码块为该代码块
    if (state & Error || state & End || !(state & Begin) ||
        document()->lastBlock() == block)
        return;
    //unfolding为否（未折叠)
    bool unfolding = state & Folded;

    if (unfolding)//如果已折叠
    {
        block.setUserState(block.userState() & ~Folded);
        qDebug()<<"block.userState() & ~Folded"<<(block.userState() & ~Folded);
    }
    else{
        block.setUserState(block.userState() | Folded);

    }

    int previousBlockState = block.previous().userState();
    int endBraceDepth = previousBlockState & Error ? 0 : previousBlockState >> StateShift;

    int braceDepth;
    int skipDepth = 0;

    while ((block = block.next()).isValid()) {
        int state = block.userState();
        braceDepth = state >> StateShift;

        if (unfolding){//如果状态同时为begin和Folded
            if (state & Begin && !skipDepth && state & Folded) {
                skipDepth = block.previous().userState() >> StateShift;
            } else if (skipDepth) {
                if (braceDepth == skipDepth)
                    skipDepth = 0;

                continue;
            }
        }

        block.setVisible(unfolding);

        if (braceDepth <= endBraceDepth)
            break;
    }
}
bool Editor::SLOT_FindPrivious(QString keyword)//寻找之前的
{

//    qDebug()<<"Finding :"<<keyword<<" "<<this->find(keyword,QTextDocument::FindBackward);
    QTextCursor cursor = textCursor();

    cursor = document()->find(keyword, cursor,QTextDocument::FindBackward);
    if(cursor.isNull()){
        return false;
    }
//    if (!cursor.block().isVisible())
//        FoldUnfoldAll(false);
    setTextCursor(cursor);
    return true;

}
bool Editor::SLOT_FindKeywords(QString keyword)//寻找关键字
{
    QTextCursor cursor = textCursor();
    cursor = document()->find(keyword, cursor);
    if(cursor.isNull()){
        return false;
    }
//    if (!cursor.block().isVisible())
//        FoldUnfoldAll(false);
    setTextCursor(cursor);
    return true;
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

QCompleter *Editor::completer() const
{
    return c;
}

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

QString Editor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void Editor::focusInEvent(QFocusEvent *e)
{
    if (c)
        c->setWidget(this);
    QPlainTextEdit::focusInEvent(e);
}

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

    QTextCursor completionText;
    completionText=textCursor();
    completionText.select(QTextCursor::LineUnderCursor);
    if(!(e->modifiers().testFlag(Qt::ControlModifier) && e->key() == Qt::Key_Z)&&!(e->modifiers().testFlag(Qt::ControlModifier) && e->key() == Qt::Key_Y))
    {
        if(e->text().right(1)=="{")
        {
            addBraceRight();
        }
        else if(e->text().right(1)=="(")
        {
            insertCompletion(")");
        }
        else if(e->text().right(1)=="[")
        {
            insertCompletion("]");
        }
        else if(e->text().right(1)=="\r")
        {
            autoIndent(true);
        }
        else if(completionText.selectedText()==NULL)
        {
            if(e->text().right(1)=="\b")
            {
            }
            else
            {
                autoIndent(true);
            }
        }
    }

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

    int space = 3 + fontMetrics().averageCharWidth() * digits;

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
void Editor::SLOT_ChangeLineNum(int num){
    this->setTextCursor(QTextCursor(document()->findBlockByNumber(num-1)));
}

void Editor::FoldCurrent(){

    QTextBlock currentBlock=document()->findBlockByLineNumber(this->textCursor().blockNumber());
    int state=0;//0->进行折叠,1->展开
    int nextNum=CountLeftKuohao(currentBlock);
    if(currentBlock.userState()&Begin){
        state=1;//如果已折叠,将模式改为展开
        currentBlock.setUserState(currentBlock.userState()&!Begin);//去掉begin标记
    }else{
        if(nextNum<=0){//如果该行左括号数量小等于右括号
            return;
        }
        currentBlock.setUserState(currentBlock.userState()|Begin);//设置为折叠开头
    }

    int begin=this->textCursor().blockNumber();
    int end=0;
    QString texttemp;
    while(currentBlock.next().isValid())
    {
        nextNum=nextNum+CountLeftKuohao(currentBlock.next());
            if(nextNum<=0){//索引成功
                end=currentBlock.blockNumber()+1;
                break;
            }
        //啥都没找到
        currentBlock=currentBlock.next();
    }
    QTextBlock blktemp;
    if(!state){//如果未折叠
        for(int i=begin+1;i<end;i++){
            blktemp=document()->findBlockByNumber(i);
            blktemp.setVisible(false);
            blktemp.setUserState((blktemp.userState())|Folded);
        }    }else{
        for(int i=begin+1;i<end;i++){
            blktemp=document()->findBlockByNumber(i);
            qDebug()<<"i"<<i<<"blktext"<<blktemp.text();
            blktemp.setVisible(true);
            blktemp.setUserState((blktemp.userState())&!Folded);//去掉Folded标记
        }
    }

    resizeEvent(new QResizeEvent(QSize(0, 0), size()));
}
int Editor::CountLeftKuohao(QTextBlock block)
{
    QString text=block.text();
    int l=text.count("{");
    int r=text.count("}");
    return l-r;
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
        if(block.userState()==Debug){
            painter.setPen(Qt::red);
            painter.drawText(-2, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, QString::number(blockNumber + 1));
        }else
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

void Editor::mouseDoubleClickEvent(QMouseEvent *){
    QTextBlock b=document()->findBlockByLineNumber(this->textCursor().blockNumber());
    //首先判断这次双击是不是为了折叠代码
    if(b.text().contains('{')&&b.userState()!=Begin){
        this->FoldCurrent();
    }
    else if(b.userState()&Debug)b.setUserState(b.userState()&!Debug);//把debug状态去掉
    else b.setUserState(b.userState()|Debug);//把它的状态增加一个debug
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


void Editor::autoIndent(bool temp)
{
    this->moveCursor(QTextCursor::Up);
    QTextCursor cursor=textCursor();
    cursor.select(QTextCursor::LineUnderCursor);
    QString previousRowText=cursor.selectedText();
    this->moveCursor(QTextCursor::Down);
    this->moveCursor(QTextCursor::StartOfLine);
    bool includeBraceLeft=previousRowText.contains("{");
    int spaceNumber=0;
    foreach(QChar qc,previousRowText)
    {
        if(qc==" ")
        {
            spaceNumber++;
        }
        else break;
    }
    if(includeBraceLeft)
    {
        if(temp) spaceNumber+=4;
    }
    for(int i=0;i<spaceNumber;i++)
    {
        this->insertPlainText(" ");
    }
}

void Editor::addBraceRight()
{
    this->insertPlainText("\n");
    autoIndent(false);
    this->insertPlainText("}");
    this->moveCursor(QTextCursor::Up);
    this->moveCursor(QTextCursor::EndOfLine);
}

