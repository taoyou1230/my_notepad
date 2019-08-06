#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QFileInfo>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <replace/replacedialog.h>
#include <search/searchdialog.h>

namespace Ui {
class NotePad;
}

class NotePad : public QMainWindow
{
    Q_OBJECT

public:
    explicit NotePad(QWidget *parent = 0);
    ~NotePad();
    //加载文件
    void loadFromFile(QString fileName);



public slots:
    /******菜单项******/
    /*文件*/
    //新建
    void slotNew();
    //打开
    void slotOpen();
    //保存
    void slotSave();
    //另存为
    void slotSaveAs();
    //页面设置
    void slotPageSet();
    //打印
    void slotPrint();
    //退出
    void slotExit();

    /*编辑*/
    //撤销
    void slotRevoke();
    //剪切
    void slotShear();
    //复制
    void slotCopy();
    //粘贴
    void slotPaste();
    //删除
    void slotDelete();
    //查找
    void slotFind();
    //查找下一个
    void slotFindNext();
    //替换
    void slotReplace();
    //转到
    void slotGoto();
    //全选
    void slotSelectAll();
    //时间/日期
    void slotTimeOrDate();

    /*格式*/
    //自行换行
    void slotWrapText();
    //字体
    void slotTypeface();

    /*查看*/
    //状态栏
    void slotStatusBar();

    /*帮助*/
    //查看帮助
    void slotViewHelp();
    //关于记事本
    void slotAbout();

    /******文本框******/
//    void slotCopyAvailable(bool);
//    void slotCursorPositionChanged();
//    void slotRedoAvailable(bool);
//    void slotSelectionChanged();
//    void slotTextChanged();
//    void slotUndoAvailable(bool);

private:
    Ui::NotePad *ui;
    QString fileName;
    QString lastDir;
    SearchDialog *searchDialog = Q_NULLPTR;
    ReplaceDialog *replaceDialog = Q_NULLPTR;
    //初始化
    void init();
    //保存文件
    bool saveFile();
    //保存文件
    bool saveFile(QString fileName);
    //另存文件
    bool saveFileAs();
    //设置文件名
    void setFileName(QString fileName);
    //确认保存
    bool confirmSave();
};

#endif // NOTEPAD_H
