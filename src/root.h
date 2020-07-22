#ifndef ROOT_H
#define ROOT_H

#include <QDialog>
#include "specs.h"
#include "sysapi.h"

namespace Ui {
class root;
}

class root : public QDialog
{
    Q_OBJECT

public:
    root(specs *os, SysAPI *term);
    ~root();

private slots:
    void on_buttonBox_accepted();

private:
    specs *itsOS;
    SysAPI *itsTerm;
    Ui::root *ui;
};

#endif // ROOT_H
