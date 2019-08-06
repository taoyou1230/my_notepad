#ifndef GOTODIALOG_H
#define GOTODIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>

namespace Ui {
class GotoDialog;
}

class GotoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GotoDialog(QWidget *parent = 0);
    ~GotoDialog();
    //设置行号
    void setLineNumber(int currLine, int maxLineCount);
    //跳转行
    int gotoLine;

public Q_SLOTS:
    void accept();

private:
    Ui::GotoDialog *ui;
    //最大行数
    int maxLineCount;
    void showMessage(QString title);
};

#endif // GOTODIALOG_H
