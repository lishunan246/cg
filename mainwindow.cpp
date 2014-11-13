#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    element_count=0;
    connect(
                ui->widget,
                SIGNAL(glelement_added(QListWidgetItem* )),
                this,
                SLOT(add_item(QListWidgetItem* ))
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
    int count=ui->listWidget->count();
    ui->listWidget->insertItem(count-1,l);

    ui->statusBar->showMessage("ok",0);
}

