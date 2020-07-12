#ifndef SPECS_H
#define SPECS_H

// Structuring specifications of OS

#include <iostream>
#include <QString>

class specs
{
public:
    specs(QString kernel, QString distro, QString de);
    ~specs();
    QString getKernel() const { return itsKernel; }
    QString getDistro() const { return itsDistro; }
    QString getDe() const { return itsDe; }
    specs() { }
private:
    QString itsKernel;
    QString itsDistro;
    QString itsDe;
};

#endif // SPECS_H
