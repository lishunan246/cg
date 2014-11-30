#ifndef LIGHTDIALOG_H
#define LIGHTDIALOG_H

#include <QDialog>

namespace Ui {
class LightDialog;
}

class LightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LightDialog(QWidget *parent = 0);
    ~LightDialog();

private:
    Ui::LightDialog *ui;
};

#endif // LIGHTDIALOG_H
