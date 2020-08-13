#include "root.h"
#include "ui_root.h"

root::root(specs *os, SysAPI *term) :
    QDialog(nullptr),
    itsOS(os),
    itsTerm(term),
    ui(new Ui::root)
{
    ui->setupUi(this);
    ui->sudo->setPlaceholderText("sudo password");
    ui->sudo->setEchoMode(QLineEdit::Password);
}

root::~root()
{
    delete ui;
}

void root::on_buttonBox_accepted()
{
    itsOS->setSudo(ui->sudo->text());
}
