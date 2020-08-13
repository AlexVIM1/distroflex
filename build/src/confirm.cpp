#include "confirm.h"
#include "ui_confirm.h"

confirm::confirm(QString operation) :
    QDialog(nullptr),
    ui(new Ui::confirm),
    itsResult(false)
{
    ui->setupUi(this);
    ui->label->setText(operation);
}

confirm::~confirm()
{
    delete ui;
}

void confirm::on_buttonBox_accepted()
{
    itsResult = true;
}
