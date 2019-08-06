#include "gotodialog.h"
#include "ui_gotodialog.h"

GotoDialog::GotoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GotoDialog)
{
    ui->setupUi(this);
}

GotoDialog::~GotoDialog()
{
    delete ui;
}
