#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
                ui->widget,
                SIGNAL(glelement_added(QListWidgetItem* )),
                this,
                SLOT(add_item(QListWidgetItem* ))
                );
    connect(
                this,
                SIGNAL(glelement_selected(QListWidgetItem*)),
                ui->widget,
                SLOT(set_current(QListWidgetItem* ))
                       );
    connect(
                ui->widget,
                SIGNAL(glelement_selected(QListWidgetItem*)),
                       this,
                       SLOT(set_current(QListWidgetItem*))
                       );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::alert(QString s)
{
    QMessageBox msgBox;
    msgBox.setText(s);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
    return;
}

void MainWindow::try_close()
{
    QMessageBox msgBox;
    msgBox.setText("You are going to quit.");
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret=msgBox.exec();
    if(ret==QMessageBox::Ok)
        close();
}

void MainWindow::add_item(QListWidgetItem *l)
{

    ui->listWidget->insertItem(0,l);

    ui->listWidget->setCurrentItem(l);
    ui->statusBar->showMessage("ok",0);
}

void MainWindow::set_current(QListWidgetItem *l)
{
    ui->listWidget->setCurrentItem(l);
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    emit glelement_selected(current);
}
