#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    msgBox.setWindowTitle("CG");
    msgBox.setText(s);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
    return;
}

QString MainWindow::new_file(QString filter,QString type)
{
    QStringList fileNames;
    QFileDialog dialog(0);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(filter);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    //dialog maybe cancelled
    if(fileNames.count()==0)
        return NULL;

    QString filename=fileNames.at(0);

    if(!filename.endsWith(type,Qt::CaseInsensitive))
        filename=filename+type;

    return filename;
}

QString MainWindow::open_file(QString filter)
{
    QStringList fileNames;
    QFileDialog dialog(0);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(filter);

    dialog.setAcceptMode(QFileDialog::AcceptOpen);

    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    //dialog maybe cancelled
    if(fileNames.count()==0)
        return NULL;

    QString filename=fileNames.at(0);


    return filename;
}

void MainWindow::try_close()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Quit");
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
