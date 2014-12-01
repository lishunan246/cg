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
Light *LightDialog::getLight() const
{
    return light;
}

void LightDialog::setLight(Light *value)
{
    light = value;

    ui->isEnabledBox->setChecked(light->isEnabled);
    ui->d0->setValue(light->direction[0]);
    ui->d1->setValue(light->direction[1]);
    ui->d2->setValue(light->direction[2]);

    ui->p0->setValue(light->position[0]);
    ui->p1->setValue(light->position[1]);
    ui->p2->setValue(light->position[2]);
    ui->p3->setValue(light->position[3]);

    ui->c->setValue(light->cutoff);
}


void LightDialog::on_buttonBox_accepted()
{
    light->isEnabled=ui->isEnabledBox->isChecked();

    light->direction[0]=ui->d0->value();
    light->direction[1]=ui->d1->value();
    light->direction[2]=ui->d2->value();

    light->position[0]=ui->p0->value();
    light->position[1]=ui->p1->value();
    light->position[2]=ui->p2->value();
    light->position[3]=ui->p3->value();

    light->cutoff=ui->c->value();
}

void LightDialog::on_set_color_Btn_clicked()
{
    ColorDialog dialog;
    dialog.setLight(light);
    dialog.exec();
}
