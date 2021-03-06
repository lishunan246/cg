#ifndef LIGHTDIALOG_H
#define LIGHTDIALOG_H

#include <QDialog>
#include "light.h"
#include "colordialog.h"
namespace Ui {
class LightDialog;
}

class LightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LightDialog(QWidget *parent = 0);
    ~LightDialog();

    Light *getLight() const;
    void setLight(Light *value);

private slots:
    void on_buttonBox_accepted();

    void on_set_color_Btn_clicked();

private:
    Ui::LightDialog *ui;
    Light* light;
};

#endif // LIGHTDIALOG_H
