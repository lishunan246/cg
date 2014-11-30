#include "lightdialog.h"
#include "ui_lightdialog.h"

LightDialog::LightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LightDialog)
{
    ui->setupUi(this);
}

LightDialog::~LightDialog()
{
    delete ui;
}
