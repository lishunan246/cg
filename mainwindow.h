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

public slots:
    void try_close();
    void add_item(QListWidgetItem* l);

private:
    Ui::MainWindow *ui;
    int element_count;
};

#endif // MAINWINDOW_H
