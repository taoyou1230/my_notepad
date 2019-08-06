#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QMessageBox>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = Q_NULLPTR, QTextEdit *textEdit = Q_NULLPTR);
    ~SearchDialog();
    void activateWindow();

private:
    Ui::SearchDialog *ui;

public Q_SLOTS:
    void search();

protected:
    QTextEdit *textEdit;
};

#endif // SEARCHDIALOG_H
