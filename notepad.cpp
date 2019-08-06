#include "notepad.h"
#include "ui_notepad.h"

NotePad::NotePad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotePad)
{
    ui->setupUi(this);

    lblStatus = new QLabel();
    lblStatus->setAlignment(Qt::AlignRight);
    statusBar()->addPermanentWidget(lblStatus);

    init();
}

NotePad::~NotePad()
{
    delete ui;
}

/**
 * 初始化
 * @brief NotePad::init
 */
void NotePad::init(){
    /*文件*/
    connect(ui->actionNew,SIGNAL(triggered(bool)),this,SLOT(slotNew()));
    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(slotOpen()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(slotSave()));
    connect(ui->actionSaveAs,SIGNAL(triggered(bool)),this,SLOT(slotSaveAs()));
    connect(ui->actionPageSet,SIGNAL(triggered(bool)),this,SLOT(slotPageSet()));
    connect(ui->actionPrint,SIGNAL(triggered(bool)),this,SLOT(slotPrint()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),this,SLOT(slotExit()));
    /*编辑*/
    connect(ui->actionRevoke,SIGNAL(triggered(bool)),this,SLOT(slotRevoke()));
    connect(ui->actionShear,SIGNAL(triggered(bool)),this,SLOT(slotShear()));
    connect(ui->actionCopy,SIGNAL(triggered(bool)),this,SLOT(slotCopy()));
    connect(ui->actionPaste,SIGNAL(triggered(bool)),this,SLOT(slotPaste()));
    connect(ui->actionDelete,SIGNAL(triggered(bool)),this,SLOT(slotDelete()));
    connect(ui->actionFind,SIGNAL(triggered(bool)),this,SLOT(slotFind()));
    connect(ui->actionFindNext,SIGNAL(triggered(bool)),this,SLOT(slotFindNext()));
    connect(ui->actionReplace,SIGNAL(triggered(bool)),this,SLOT(slotReplace()));
    connect(ui->actionGoto,SIGNAL(triggered(bool)),this,SLOT(slotGoto()));
    connect(ui->actionSelectAll,SIGNAL(triggered(bool)),this,SLOT(slotSelectAll()));
    connect(ui->actionTimeOrDate,SIGNAL(triggered(bool)),this,SLOT(slotTimeOrDate()));
    /*格式*/
    connect(ui->actionWrapText,SIGNAL(triggered(bool)),this,SLOT(slotWrapText()));
    connect(ui->actionTypeface,SIGNAL(triggered(bool)),this,SLOT(slotTypeface()));
    /*查看*/
    connect(ui->actionStatusBar,SIGNAL(triggered(bool)),this,SLOT(slotStatusBar()));
    /*帮助*/
    connect(ui->actionViewHelp,SIGNAL(triggered(bool)),this,SLOT(slotViewHelp()));
    connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(slotAbout()));

    /*文本框监听*/
    connect(ui->textEdit,SIGNAL(undoAvailable(bool)),this,SLOT(slotUndoAvailable(bool)));
    connect(ui->textEdit,SIGNAL(copyAvailable(bool)),this,SLOT(slotCopyAvailable(bool)));
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(slotCursorPositionChanged()));
    connect(ui->textEdit,SIGNAL(redoAvailable(bool)),this,SLOT(slotRedoAvailable(bool)));
    connect(ui->textEdit,SIGNAL(selectionChanged()),this,SLOT(slotSelectionChanged()));
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(slotTextChanged()));

    //设置action初始状态
    setActionState();
    //加载设置
    loadSettings();

}
/**
 * @brief NotePad::loadFromFile
 * @param fileName
 */
void NotePad::loadFromFile(QString fileName){
    QFileInfo fileInfo(fileName);
    if (!fileInfo.isFile())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("提示"), tr("不能打开此文件！"), tr("确定"));
        return;
    }

    setFileName(fileName);
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
}



/******菜单项******/
/*文件*/
//新建
void NotePad::slotNew(){
    if (!confirmSave())
        return;
    ui->textEdit->clear();
    setFileName("");
}

//打开
void NotePad::slotOpen(){

}

//保存
void NotePad::slotSave(){
    saveFile();
}
//另存为
void NotePad::slotSaveAs(){
    saveFileAs();
}
//页面设置
void NotePad::slotPageSet(){
    QMessageBox::critical(this, tr("提示"), tr("抱歉，请等待后续开发！"), tr("关闭"));
}
//打印
void NotePad::slotPrint(){
    QMessageBox::critical(this, tr("提示"), tr("抱歉，请等待后续开发！"), tr("关闭"));
}
//退出
void NotePad::slotExit(){
    if(!confirmSave()){
        return;
    }
    this->close();
}

/*编辑*/
//撤销
void NotePad::slotRevoke(){
    ui->textEdit->undo();
}
//剪切
void NotePad::slotShear(){
    ui->textEdit->cut();
}
//复制
void NotePad::slotCopy(){
    ui->textEdit->copy();
}
//粘贴
void NotePad::slotPaste(){
    ui->textEdit->paste();
}
//删除
void NotePad::slotDelete(){
    ui->textEdit->textCursor().removeSelectedText();
}
//查找
void NotePad::slotFind(){
    if (replaceDialog != Q_NULLPTR && replaceDialog->isVisible())
    {
        replaceDialog->activateWindow();
        return;
    }

    if (searchDialog == Q_NULLPTR)
        searchDialog = new SearchDialog(this, ui->textEdit);
    searchDialog->show();
    searchDialog->activateWindow();
}
//查找下一个
void NotePad::slotFindNext(){
    if (searchDialog == Q_NULLPTR)
        searchDialog = new SearchDialog(this, ui->textEdit);
    searchDialog->search();
}
//替换
void NotePad::slotReplace(){
    if (searchDialog != Q_NULLPTR && searchDialog->isVisible())
    {
        searchDialog->activateWindow();
        return;
    }

    if (replaceDialog == Q_NULLPTR)
        replaceDialog = new ReplaceDialog(this, ui->textEdit);
    replaceDialog->show();
    replaceDialog->activateWindow();
}
//转到
void NotePad::slotGoto(){
    //跳转...传this以此做为其窗主，Modal状态标题栏闪烁
    GotoDialog gotoDialog(this);
    gotoDialog.setLineNumber(ui->textEdit->textCursor().blockNumber() + 1, ui->textEdit->document()->lineCount());
    if (gotoDialog.exec() == QDialog::Accepted)
    {
        int line = gotoDialog.gotoLine;
        QTextCursor cursor = ui->textEdit->textCursor();
        int position = ui->textEdit->document()->findBlockByNumber(line - 1).position();
        cursor.setPosition(position, QTextCursor::MoveAnchor);
        ui->textEdit->setTextCursor(cursor);
    }
}
//全选
void NotePad::slotSelectAll(){

}
//时间/日期
void NotePad::slotTimeOrDate(){

}

/*格式*/
//自行换行
void NotePad::slotWrapText(){

}
//字体
void NotePad::slotTypeface(){

}

/*查看*/
//状态栏
void NotePad::slotStatusBar(){
    this->statusChecked = ui->actionStatusBar->isChecked();
    ui->statusBar->setVisible(ui->actionStatusBar->isChecked());
}

/*帮助*/
//查看帮助
void NotePad::slotViewHelp(){

}
//关于记事本
void NotePad::slotAbout(){

}
//
void NotePad::slotCopyAvailable(bool enabled)
{
    ui->actionCopy->setEnabled(enabled);
}
//
void NotePad::slotCursorPositionChanged()
{
    QTextCursor tc = ui->textEdit->textCursor();
    QString info = tr("第%1行，第%2列  ").arg(tc.blockNumber() + 1).arg(tc.columnNumber());
    lblStatus->setText(info);
}
//
void NotePad::slotRedoAvailable(bool enabled)
{
}
//
void NotePad::slotSelectionChanged()
{
    QString selecdedText = ui->textEdit->textCursor().selectedText();
    //ui.actUndo
    ui->actionCopy->setEnabled(!selecdedText.isEmpty());
    ui->actionPaste->setEnabled(!selecdedText.isEmpty());
    ui->actionDelete->setEnabled(!selecdedText.isEmpty());
}
//
void NotePad::slotTextChanged()
{
    slotSelectionChanged();

    QString text = ui->textEdit->toPlainText();
    ui->actionFind->setEnabled(text != "");
    ui->actionFindNext->setEnabled(text != "");
    ui->actionGoto->setEnabled(text != "" && !ui->actionWrapText->isChecked());
}
//
void NotePad::slotUndoAvailable(bool enabled)
{
    ui->actionRevoke->setEnabled(enabled);
}


/**
 * 保存文件
 * @brief NotePad::saveFile
 * @return
 */
bool NotePad::saveFile()
{
    if (this->fileName.isEmpty())
        return saveFileAs();

    return saveFile(this->fileName);
}

/**
 * 保存文件
 * @brief NotePad::saveFile
 * @param fileName
 * @return
 */
bool NotePad::saveFile(QString fileName)
{
    if (!ui->textEdit->document()->isModified())
        return false;

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::critical(this, tr("提示"), tr("不能写入文件！"), tr("确定"));
        return false;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    setFileName(fileName);
    return true;
}

/**
 * 另存文件
 * @brief NotePad::saveFileAs
 * @return
 */
bool NotePad::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"),
        lastDir + tr("./未命名.txt"), tr("文本文档(*.txt);;所有文件(*.*)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

/**
 * 设置文件名
 * @brief NotePad::setFileName
 * @param fileName
 */
void NotePad::setFileName(QString fileName)
{
    this->fileName = fileName;
    ui->textEdit->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = tr("未命名");
    else
        shownName = QFileInfo(fileName).fileName();
    setWindowTitle(tr("%1[*] - %2").arg(shownName, tr("记事本")));
    setWindowModified(false);

    lastDir = QFileInfo(fileName).absoluteDir().absolutePath();
}

/**
 * 确认保存
 * @brief NotePad::confirmSave
 * @return
 */
bool NotePad::confirmSave()
{
    if (!ui->textEdit->document()->isModified())
        return true;

//    QMessageBox::StandardButtons sb = QMessageBox::question(this, tr("提示"), tr("是否将更改保存到 %1？")
//        .arg(this->windowTitle().replace(tr(" - 记事本"), "")),
//        tr("保存(&S)"), tr("不保存(&N)"), tr("取消"));

    QMessageBox msg;
    msg.setWindowTitle(tr("提示"));
    msg.setText(tr("是否将更改保存到 %1？")
                .arg(this->windowTitle().replace(tr(" - 记事本"), "")));
    msg.addButton(tr("保存(&S)"),QMessageBox::ActionRole);
    msg.addButton(tr("不保存(&N)"),QMessageBox::ActionRole);
    msg.addButton(tr("取消"),QMessageBox::ActionRole);
    int sb = msg.exec();
    switch (sb)
    {
    case 0:
        return saveFile();
    case 1:
        return true;
    case 2:
        return false;
    default:
        return true;
    }
}

/**
 * 设置action显示启用状态
 * @brief NotePad::setActionState
 */
void NotePad::setActionState()
{
    ui->actionRevoke->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
    ui->actionDelete->setEnabled(false);
    ui->actionFind->setEnabled(false);
    ui->actionFindNext->setEnabled(false);
    ui->actionGoto->setEnabled(false);
}

/**
 * 初始化文本框样式
 * @brief NotePad::initTextEdifUI
 */
void NotePad::initTextEdifUI()
{
    QPalette palette = ui->textEdit->palette();
    palette.setColor(QPalette::Highlight, Qt::darkGreen);
    palette.setColor(QPalette::HighlightedText, Qt::white);
    ui->textEdit->setPalette(palette);

    ui->textEdit->setAcceptDrops(false);
    setAcceptDrops(true);
}

/**
 * 加载设置
 * @brief NotePad::loadSettings
 */
void NotePad::loadSettings()
{
    //大小&位置
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Notepad", QSettings::NativeFormat);
    int x = settings.value("iWindowPosX", 0).toInt();
    int y = settings.value("iWindowPosY", 0).toInt();
    int w = settings.value("iWindowPosDX", 800).toInt();
    int h = settings.value("iWindowPosDY", 600).toInt();
    this->setGeometry(x, y, w, h);
    ui->actionWrapText->setChecked(settings.value("fWrap", true).toBool());
    ui->actionStatusBar->setChecked(settings.value("StatusBar", true).toBool());
    ui->statusBar->setVisible(ui->actionStatusBar->isChecked());
}

/**
 * 保存设置
 * @brief NotePad::saveSettings
 */
void NotePad::saveSettings()
{
    //大小&位置
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Notepad", QSettings::NativeFormat);
    settings.setValue("iWindowPosX", this->x());
    settings.setValue("iWindowPosY", this->y());
    settings.setValue("iWindowPosDX", this->width());
    settings.setValue("iWindowPosDY", this->height());
    settings.setValue("fWrap", ui->actionWrapText->isChecked());
    settings.setValue("StatusBar", ui->actionStatusBar->isChecked());
}
