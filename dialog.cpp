#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("确认");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
}

Dialog::~Dialog()
{
    delete ui;
}
