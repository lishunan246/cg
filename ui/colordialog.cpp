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
    if(light!=NULL)
    {
        light->ambient_color[0]=ui->a0->value();
        light->ambient_color[1]=ui->a1->value();
        light->ambient_color[2]=ui->a2->value();
        light->ambient_color[3]=ui->a3->value();

        light->diffuse_color[0]=ui->d0->value();
        light->diffuse_color[1]=ui->d1->value();
        light->diffuse_color[2]=ui->d2->value();
        light->diffuse_color[3]=ui->d3->value();

        light->specular_color[0]=ui->s0->value();
        light->specular_color[1]=ui->s1->value();
        light->specular_color[2]=ui->s2->value();
        light->specular_color[3]=ui->s3->value();

    }
    if(element!=NULL)
    {
        element->ambient_color[0]=ui->a0->value();
        element->ambient_color[1]=ui->a1->value();
        element->ambient_color[2]=ui->a2->value();
        element->ambient_color[3]=ui->a3->value();

        element->diffuse_color[0]=ui->d0->value();
        element->diffuse_color[1]=ui->d1->value();
        element->diffuse_color[2]=ui->d2->value();
        element->diffuse_color[3]=ui->d3->value();

        element->specular_color[0]=ui->s0->value();
        element->specular_color[1]=ui->s1->value();
        element->specular_color[2]=ui->s2->value();
        element->specular_color[3]=ui->s3->value();
    }

    close();
}

void ColorDialog::setCurrentElement(GLElement *e)
{
    element=e;

    ui->a0->setValue(e->ambient_color[0]);
    ui->a1->setValue(e->ambient_color[1]);
    ui->a2->setValue(e->ambient_color[2]);
    ui->a3->setValue(e->ambient_color[3]);

    ui->d0->setValue(e->diffuse_color[0]);
    ui->d1->setValue(e->diffuse_color[1]);
    ui->d2->setValue(e->diffuse_color[2]);
    ui->d3->setValue(e->diffuse_color[3]);

    ui->s0->setValue(e->specular_color[0]);
    ui->s1->setValue(e->specular_color[1]);
    ui->s2->setValue(e->specular_color[2]);
    ui->s3->setValue(e->specular_color[3]);

}

void ColorDialog::setLight(Light *e)
{
    light=e;

    ui->a0->setValue(e->ambient_color[0]);
    ui->a1->setValue(e->ambient_color[1]);
    ui->a2->setValue(e->ambient_color[2]);
    ui->a3->setValue(e->ambient_color[3]);

    ui->d0->setValue(e->diffuse_color[0]);
    ui->d1->setValue(e->diffuse_color[1]);
    ui->d2->setValue(e->diffuse_color[2]);
    ui->d3->setValue(e->diffuse_color[3]);

    ui->s0->setValue(e->specular_color[0]);
    ui->s1->setValue(e->specular_color[1]);
    ui->s2->setValue(e->specular_color[2]);
    ui->s3->setValue(e->specular_color[3]);
}
