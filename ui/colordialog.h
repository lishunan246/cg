#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include "glelement.h"
namespace Ui {
class ColorDialog;
}

class ColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorDialog(QWidget *parent = 0);
    ~ColorDialog();
    void accept();
    void setCurrentElement(GLElement* e);
private:
    Ui::ColorDialog *ui;
    GLElement* element;
};

#endif // COLORDIALOG_H
