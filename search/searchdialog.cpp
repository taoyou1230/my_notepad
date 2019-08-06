#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent, QTextEdit *textEdit) :
    QDialog(parent),
    ui(new Ui::SearchDialog),
    textEdit(textEdit)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

    ui->label->setBuddy(ui->lineEdit);
    ui->searchButton->setEnabled(false);
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(ui->lineEdit, &QLineEdit::textChanged, [=]()
    {
        ui->searchButton->setEnabled(ui->lineEdit->text() != "");
    });
    //监听取消按钮
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

/**
 * 弹窗置顶
 * @brief SearchDialog::activateWindow
 */
void SearchDialog::activateWindow()
{
    QDialog::activateWindow();

    ui->lineEdit->setText(textEdit->textCursor().selectedText());
    ui->lineEdit->selectAll();

}

/**
 * 查找内容
 * @brief SearchDialog::search
 */
void SearchDialog::search()
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty())
        return;

    QTextDocument::FindFlags findFlags;
    if (ui->cbCaseSensitive->isChecked())
        findFlags = QTextDocument::FindCaseSensitively;
    if (ui->rbUp->isChecked())
        findFlags |= QTextDocument::FindBackward;
    bool found = textEdit->find(text, findFlags);

    if (!found)
        QMessageBox::information(this, tr("记事本"), tr("找不到\"%1\"").arg(text), QMessageBox::Ok);
}
