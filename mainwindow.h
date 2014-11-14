#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static void alert(QString s);
    static QString new_file(QString filter, QString type);
    static QString open_file(QString filter);

public slots:
    void try_close();
    void add_item(QListWidgetItem* l);
    //when an element is deleted, the currentElement must be updated
    void set_current(QListWidgetItem* l);
signals:
    void glelement_selected(QListWidgetItem* l);

private slots:
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
