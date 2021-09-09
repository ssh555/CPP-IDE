#include "editor.h"
#include <QtWidgets>
#include<QPlainTextEdit>
#include<QDebug>
#include "config.h"
#include "highlighter.h"
#include "config.h"
#include "uiinterface.h"
Editor::Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    this->Init();

}
void Editor::Init()
{
    //改了个可爱的字体
    setting=new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    int fontsize=setting->value("editorfontsize").toUInt();
    QString fontname=setting->value("CodeFont").toString();
    this->setFont(QFont(fontname,fontsize));
    SLOT_UpdateLineNumberAreaWidth(0);
    int fontWidth = QFontMetrics(this->currentCharFormat().font()).averageCharWidth();
    this->setTabStopDistance( 4 * fontWidth );
    Set_Mode(BROWSE);
    //设置高亮
    highlighter = new Highlighter(this->document());
    highlighter->Start_Highlight();
    //设置旁边竖条的颜色
    //qDebug()<<setting->value("LineColor").toString();
    LineNumberColor=setting->value("LineColor").toString();
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(SLOT_UpdateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(SLOT_UpdateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(SLOT_HighlightCurrentLine()));
    //    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(SLOT_BracketMatch()));
}
void Editor::mouseDoubleClickEvent(QMouseEvent *){
    QTextBlock b=document()->findBlockByNumber(this->textCursor().blockNumber());
    //首先判断这次双击是不是为了折叠代码
    if(b.text().contains('{')){
        this->FoldCurrent();
    }
    else if(b.userState()&Debug){
        BlockState t = Debug;
        b.setUserState(b.userState()&!t);//把debug状态去掉
    }

    else {
        b.setUserState(b.userState()|Debug);//把它的状态增加一个debug
        //qDebug()<<b.userState();
    }
}
void Editor::FoldCurrent(){

    QTextBlock currentBlock=document()->findBlockByNumber(this->textCursor().blockNumber());
    int state=0;//0->进行折叠,1->展开
    //qDebug()<<currentBlock.userState();
    if(currentBlock.userState()&Begin){
        state=1;//如果已折叠,将模式改为展开
        BlockState t = Begin;
        currentBlock.setUserState(currentBlock.userState()&~t);//去掉begin标记
    }else{
        currentBlock.setUserState(currentBlock.userState()|Begin);//设置为折叠开头
    }
    int begin=this->textCursor().blockNumber();
    int end=0;
    QString texttemp;
    int nextNum=0;

    texttemp=currentBlock.text();
    if(texttemp.contains("{")&&texttemp.contains("}"))
    {

        int firsttLeftBrace=texttemp.indexOf("{",0);
        texttemp.remove(0,firsttLeftBrace);
        foreach(QChar qc,texttemp)
        {
            if(qc=="{") nextNum++;
            else if(qc=="}") nextNum--;
        }
    }
    else
    {
        foreach(QChar qc,texttemp)
        {
            if(qc=="{") nextNum++;
        }
    }

    int quote=0;
    for(;currentBlock.next().isValid();)
    {
        texttemp=currentBlock.next().text(); //qDebug()<<texttemp;
        quote = texttemp.count("\"");
        texttemp.replace("\\\"","");
        while(quote>0&&(quote%2==0))
        {
            int quoteLeft=texttemp.indexOf("\"",0);
            int quoteRight=texttemp.indexOf("\"",quoteLeft+1);
            texttemp.remove(quoteLeft,quoteRight-quoteLeft+1);
            quote-=2;
        }
        if(texttemp.contains("{")||texttemp.contains("}"))
        {//判断该行是否匹配成功
            foreach(QChar qc,texttemp)
            {
                if(qc=="{")
                    nextNum++;
                if(qc=="}")
                    nextNum--;
                if(nextNum==0) break;
            }
        }
        if(nextNum==0)
        {//索引成功
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
        }
    }else{
        for(int i=begin+1;i<end;i++){
            blktemp=document()->findBlockByNumber(i);
            if(blktemp.userState()&Folded)
            {
                //qDebug()<<"i"<<i<<"blktext"<<blktemp.text()<<blktemp.userState();
                blktemp.setVisible(true);
                BlockState t = Folded;
                blktemp.setUserState((blktemp.userState())&~t);//去掉Folded标记
            }
        }
    }



    resizeEvent(new QResizeEvent(QSize(0, 0), size()));
}


void Editor::wheelEvent(QWheelEvent *e)
{
    if(e->modifiers() == Qt::ControlModifier) {
        if(e->delta() > 0){                    // 当滚轮远离使用者时
            emit(SIGNAL_ChangeFont(true));               // 进行放大
        }else{                                     // 当滚轮向使用者方向旋转时
            emit(SIGNAL_ChangeFont(false));               // 进行缩小
        }
    }else{
        //QTextCursor cursor = textCursor();
        QScrollBar* scrollBar = this->verticalScrollBar();
        //一次滚动2行
        if(e->delta() > 0){                    // 向上滚动
            //cursor.movePosition(QTextCursor::Up,QTextCursor::MoveAnchor,1);
            scrollBar->setValue(scrollBar->value()-2);
        }else{                                     // 向下滚动
            //cursor.movePosition(QTextCursor::Down,QTextCursor::MoveAnchor,1);
            scrollBar->setValue(scrollBar->value()+2);
        }
        //this->setTextCursor(cursor);
    }
}
void Editor::findPrivious(QString findword)
{
    this->isChanged=true;
    SLOT_ReplacePrivious(findword,findword);
    this->isChanged=false;
}
//全部替换函数
void Editor::SLOT_ReplaceWhole(QString findword,QString replaceword)
{
    QTextCursor cursor = textCursor();

    cursor.setPosition(0, QTextCursor::MoveAnchor);
    setTextCursor(cursor);

    while (SLOT_ReplaceKeywords(findword, replaceword));
}
//获取所有的断点,传出一个qvector的值
QVector<qint32> Editor::GetBreakPoints()
{
    QVector<qint32> *breakpoints=new QVector<qint32>;
    QTextBlock b=document()->firstBlock();
    while(b.next().isValid()){
        if(b.userState()&Debug){
            breakpoints->append(b.blockNumber());
        }
        b=b.next();
    }

    return *breakpoints;
}
//替换下一个

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


void Editor::ChangeCodeStyle(){
    highlighter = new Highlighter(this->document());
    highlighter->Start_Highlight();
    this->LineNumberColor=setting->value("LineColor").toString();
    //qDebug()<<setting->value("LineColor").toString();
}


bool Editor::SLOT_FindPrivious(QString keyword)//寻找之前的
{

    //    qDebug()<<"Finding :"<<keyword<<" "<<this->find(keyword,QTextDocument::FindBackward);
    QTextCursor cursor = textCursor();
    cursor = document()->find(keyword, cursor,QTextDocument::FindBackward);
    if(cursor.isNull()){
        return false;
    }
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
//获取指针选中的文字
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
//按键响应事件,F2折叠注释,F3展开注释
void Editor::keyPressEvent(QKeyEvent *e)
{
    //
    if(e->key()==Qt::Key_F2)
    {
        explainFold();
        //qDebug()<<"fold happen";
    }
    if(e->key()==Qt::Key_F3)
    {
        explainUnfold();
        //qDebug()<<"unfold happen";
    }

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
            insertPlainText(")");
            this->moveCursor(QTextCursor::Left);
        }
        else if(e->text().right(1)=="[")
        {
            insertPlainText("]");
            this->moveCursor(QTextCursor::Left);
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
}
/*
void Editor::insertCompletion(const QString& completion)
{
    if (c->widget() != this)
        return;
    QTextCursor tc = textCursor();

    //qDebug()<<completion.length();
    //qDebug()<<c->completionPrefix().length();
    int extra = completion.length()- c->completionPrefix().length();

    //qDebug()<<extra;

#ifndef QT_NO_CURSOR

    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    tc.select(QTextCursor::WordUnderCursor);
    //qDebug()<<"selecte text: "+tc.selectedText ();
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
//计算行号大小
int Editor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().averageCharWidth() * (digits+1);

    return space;
}
//更新行号大小
void Editor::SLOT_UpdateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}
//更新行号
void Editor::SLOT_UpdateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        SLOT_UpdateLineNumberAreaWidth(0);
}
//重新安排大小
void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}
//当前行高亮
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
    SLOT_BracketMatch(extraSelections);
    setExtraSelections(extraSelections);

}
//更改光标位置(响应debuger)
void Editor::SLOT_ChangeLineNum(int num){
    this->setTextCursor(QTextCursor(document()->findBlockByNumber(num-1)));
}

//行号绘制

void Editor::Line_Number_Area_Paint_Event(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);

    painter.fillRect(event->rect(), QColor(LineNumberColor));
    //设置画笔大小
    painter.setFont(QFont(setting->value("CodeFont").toString(),setting->value("editorfontsize").toInt()));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if(block.userState()&Debug and block.isVisible()){
            painter.setPen(Qt::red);
            painter.drawText(-2, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, QString::number(blockNumber + 1));
            QPen *pen=new QPen();
            pen->setWidth(fontMetrics().height()/2);
            pen->setColor(Qt::red); // 设置画笔为黄色
            painter.setPen(*pen); // 设置画笔
            painter.drawPoint(0,(top+bottom)/2);
        }
        else  if (block.isVisible() && bottom >= event->rect().top()) {
            if(block.userState()&Begin and block.isVisible()){
                painter.setPen(Qt::black);
                painter.drawText(-2-fontMetrics().height()/2, top, lineNumberArea->width(), fontMetrics().height(),
                                 Qt::AlignRight, "+");

            }
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


//设置编辑模式
void Editor::Set_Mode(editorMode mode)
{
    if(mode == BROWSE)
    {
        this->setReadOnly(true);

        SLOT_HighlightCurrentLine();
    }
    else if(mode == EDIT)
    {
        this->setReadOnly(false);

        SLOT_HighlightCurrentLine();
    }
}

//自动缩进
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
    int beforeTabSpace=0;
    foreach(QChar qc,previousRowText)
    {
        if(qc==" ")
        {
            spaceNumber++;
            beforeTabSpace++;
            if(beforeTabSpace==4) beforeTabSpace=0;
        }
        else if(qc=="\x9")
        {
            spaceNumber+=4-beforeTabSpace;
            beforeTabSpace=0;
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

//添加右括号
void Editor::addBraceRight()
{
    this->insertPlainText("\n");
    autoIndent(false);
    this->insertPlainText("}");
    this->moveCursor(QTextCursor::Up);
    this->moveCursor(QTextCursor::EndOfLine);
}
//注释折叠
void Editor::explainFold()
{
    QTextBlock block=document()->firstBlock();
    QString text=block.text().simplified();
    for(;block.isValid();)
    {
        text=block.text().simplified();
        if(text.size()>=2&&text.at(0)=="/")
        {
            if(text.at(1)=="/")
            {
                block.setVisible(false);
                block.setUserState(block.userState()|Nested);
                //qDebug()<<block.userState()<<block.blockNumber()<<"fold";
            }
            else if(text.at(1)=="*")
            {
                for(;block.isValid();)
                {
                    text=block.text().simplified();
                    block.setVisible(false);
                    block.setUserState(block.userState()|Nested);
                    //qDebug()<<block.userState()<<block.blockNumber()<<"fold";
                    if(text.contains("*/")) break;
                    block=block.next();
                }
            }
        }
        block=block.next();
    }
    resizeEvent(new QResizeEvent(QSize(0, 0), size()));
}
//注释展开
void Editor::explainUnfold()
{
    QTextBlock block=document()->firstBlock();
    for(;block.isValid();)
    {
        if(block.userState()&Nested)
        {
            block.setVisible(true);
            block.setUserState(block.userState()&(~Nested));
        }
        block=block.next();
    }
    resizeEvent(new QResizeEvent(QSize(0, 0), size()));
}

void Editor::SLOT_BracketMatch(QList<QTextEdit::ExtraSelection> &extraSelections)
{
    QTextCursor cursorQuote=textCursor();
    int currentPosition=cursorQuote.positionInBlock();
    cursorQuote.select(QTextCursor::LineUnderCursor);
    QString texttemp=cursorQuote.selectedText();
    int quote=0;
    int quotePosition=0;
    quote = texttemp.count("\"");
    while(quote>0&&(quote%2==0))
    {
        int quoteLeft=texttemp.indexOf("\"",quotePosition);
        int quoteRight=texttemp.indexOf("\"",quoteLeft+1);
        if(currentPosition>quoteLeft&&currentPosition<quoteRight) return;
        quote-=2;
        quotePosition=quoteRight+1;
    }

    //增减数组需要修改for循环的条件
    QChar brace[6]={'(','[','{',')',']','}'};

    QTextDocument *doc = this->document();
    QTextCursor cursor = textCursor();
    cursor.clearSelection();
    int position = cursor.position();


    //可以修改 selection.format 以修改显示样式
    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(Qt::green);
    //    selection.format.setProperty(QTextFormat::FullWidthSelection, true);


    QTextCursor cursorBegin;
    QTextCursor cursorEnd;

    QChar c, charBegin=' ', charEnd=' ';

    bool whetherInQuote=false;

    //向后找
    //判断是否是需要匹配的字符
    for(int i=0;i<3;i++) {
        if(i<3 && doc->characterAt(position) == brace[i]) {
            charBegin = brace[i];
            charEnd = brace[i+3];
            break;
        }
    }
    //查找主体
    if (!cursor.atBlockEnd() && charBegin!=' ') {
        position++;     //记录下标

        cursorBegin = QTextCursor(cursor);
        cursorBegin.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);

        int counter = 1;        //用于数左右括号的数量，为左括号则+1，为右括号则-1，counter为0则匹配成功

        while (!(c = doc->characterAt(position)).isNull()) {
            if(c=="\"")
            {
                if(doc->characterAt(position-1)=="\\")
                {
                    whetherInQuote=!whetherInQuote;
                }
                whetherInQuote=!whetherInQuote;
            }
            if(whetherInQuote)
            {
                position++;
                continue;
            }
            if (c == charBegin) {
                counter++;
            }
            else if (c == charEnd) {
                counter--;
                if (0 == counter) {     //counter为0，匹配成功，修改样式
                    cursorEnd = QTextCursor(doc);
                    cursorEnd.setPosition(position);
                    cursorEnd.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);

                    if (!isReadOnly()) {
                        selection.cursor = cursorEnd;
                        //                        qDebug()<<cursorEnd.position();
                        extraSelections.append(selection);

                        selection.cursor = cursorBegin;
                        //                        qDebug()<<cursorBegin.position();
                        extraSelections.append(selection);
                    }
                    whetherInQuote=false;
                    break;
                }
            }
            position++;
        }
    }
    //向前找，原理与 向后找 一样
    charBegin=' ', charEnd=' ';
    position = cursor.position()-1;
    for(int i=3;i<6;i++) {
        if(doc->characterAt(position) == brace[i]) {
            charBegin = brace[i-3];
            charEnd = brace[i];
            break;
        }
    }

    if (!cursor.atBlockStart() && charEnd!=' ') {
        cursorEnd = QTextCursor(cursor);
        cursorEnd.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);

        int counter = 0;

        while (!(c = doc->characterAt(position)).isNull()) {
            if(c=="\"")
            {
                if(doc->characterAt(position-1)=="\\")
                {
                    whetherInQuote=!whetherInQuote;
                }
                whetherInQuote=!whetherInQuote;
            }
            if(whetherInQuote)
            {
                position--;
                continue;
            }
            if (c == charEnd) {
                counter++;
            }
            else if (c == charBegin) {
                counter--;
                if (0 == counter) {
                    cursorBegin = QTextCursor(doc);
                    cursorBegin.setPosition(position);
                    cursorBegin.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);

                    if (!isReadOnly()) {
                        selection.cursor = cursorBegin;
                        //                        qDebug()<<cursorBegin.position();
                        extraSelections.append(selection);

                        selection.cursor = cursorEnd;
                        //                        qDebug()<<cursorEnd.position();
                        extraSelections.append(selection);
                    }
                    whetherInQuote=false;
                    break;
                }
            }
            position--;
        }
    }
}

