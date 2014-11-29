#include "colordialog.h"
#include "ui_colordialog.h"

ColorDialog::ColorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorDialog)
{
    ui->setupUi(this);
}

ColorDialog::~ColorDialog()
{
    delete ui;
}

void ColorDialog::accept()
{
    float rgba[4];
    rgba[0]=(float)ui->r_c->value();
    rgba[1]=(float)ui->g_c->value();
    rgba[2]=(float)ui->b_c->value();
    rgba[3]=(float)ui->a_c->value();

    bool is_diffuse=ui->diffuse->isChecked();
    bool is_specular=ui->specular->isChecked();
    bool is_ambient=ui->ambient->isChecked();

    element->set_color(rgba,is_diffuse,is_specular,is_ambient);
    close();
}

void ColorDialog::setCurrentElement(GLElement *e)
{
    element=e;
}
