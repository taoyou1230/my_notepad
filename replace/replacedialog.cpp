#include "replacedialog.h"
#include "ui_replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent,QTextEdit *textEdit) :
    QDialog(parent),
    ui(new Ui::ReplaceDialog),
    textEdit(textEdit)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    //初始化
    initDialog();
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}
/**
 * 初始化
 * @brief ReplaceDialog::initDialog
 */
void ReplaceDialog::initDialog()
{
    ui->label->setBuddy(ui->lineEdit);
    ui->lblReplace->setBuddy(ui->replaceEdit);
    ui->searchButton->setEnabled(false);
    ui->replaceButton->setEnabled(false);
    ui->replaceAllButton->setEnabled(false);
    QObject::connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(search()));
    QObject::connect(ui->replaceButton, SIGNAL(clicked()), this, SLOT(replace()));
    QObject::connect(ui->replaceAllButton, SIGNAL(clicked()), this, SLOT(replaceAll()));
    QObject::connect(ui->lineEdit, &QLineEdit::textChanged, [=]()
    {
        ui->searchButton->setEnabled(ui->lineEdit->text() != "");
        ui->replaceButton->setEnabled(ui->lineEdit->text() != "");
        ui->replaceAllButton->setEnabled(ui->lineEdit->text() != "");
    });
    //关闭弹窗
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(reject()));
}

/**
 * 弹窗置顶
 * @brief ReplaceDialog::activateWindow
 */
void ReplaceDialog::activateWindow()
{
    QDialog::activateWindow();

    ui->lineEdit->setText(textEdit->textCursor().selectedText());
    ui->lineEdit->selectAll();
}

/**
 * 查询
 * @brief ReplaceDialog::search
 * @param showWarn
 * @return
 */
bool ReplaceDialog::search(bool showWarn)
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty())
        return false;

    QTextDocument::FindFlags findFlags;
    if (ui->cbCaseSensitive->isChecked())
        findFlags = QTextDocument::FindCaseSensitively;
    bool found = textEdit->find(text, findFlags);

    if (!found && showWarn)
        QMessageBox::information(this, tr("记事本"), tr("找不到\"%1\"").arg(text), QMessageBox::Ok);
    return found;
}

/**
 * 替换
 * @brief ReplaceDialog::replace
 */
void ReplaceDialog::replace()
{
    bool found = search();
    if (!found)
        return;

    QTextCursor textCursor = textEdit->textCursor();
    QString replaceText = ui->replaceEdit->text();
    textCursor.insertText(replaceText);

    //寻找下一个
    search();
}

/**
 * 替换全部
 * @brief ReplaceDialog::replaceAll
 */
void ReplaceDialog::replaceAll()
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty())
        return;

    QTextDocument::FindFlags findFlags;
    if (ui->cbCaseSensitive->isChecked())
        findFlags = QTextDocument::FindCaseSensitively;
    QString replaceText = ui->replaceEdit->text();
    while (textEdit->find(text, findFlags))
    {
        QTextCursor textCursor = textEdit->textCursor();
        textCursor.insertText(replaceText);
    }
    //往回找
    findFlags |= QTextDocument::FindBackward;
    while (textEdit->find(text, findFlags))
    {
        QTextCursor textCursor = textEdit->textCursor();
        textCursor.insertText(replaceText);
    }
}
