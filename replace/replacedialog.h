#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QMessageBox>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = 0, QTextEdit *textEdit = Q_NULLPTR);
    ~ReplaceDialog();
    //弹窗置顶
    void activateWindow();

public Q_SLOTS:
    //查询
    bool search(bool showWarn = true);
    //替换
    void replace();
    //全部替换
    void replaceAll();

private:
    Ui::ReplaceDialog *ui;
    //主页面文本框
    QTextEdit *textEdit;
    //初始化
    void initDialog();
};

#endif // REPLACEDIALOG_H
