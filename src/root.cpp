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
}

root::~root()
{
    delete ui;
}

void root::on_buttonBox_accepted()
{
    itsOS->setSudo(ui->sudo->text());
    itsTerm->start("sh");
    itsTerm->write("echo $USER");
    itsTerm->closeWriteChannel();
    itsTerm->waitForFinished();
    itsOS->setUser(itsTerm->readAll());
}
