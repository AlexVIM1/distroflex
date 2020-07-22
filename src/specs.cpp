#include "specs.h"

// Initializing data

specs::specs(QString kernel, QString distro, QString de) :
    itsKernel(kernel),
    itsDistro(distro),
    itsDe(de)
{

}

specs::~specs()
{
    itsKernel = "";
    itsDistro = "";
    itsDe = "";
    itsCores = "";
    itsThreads = "";
    itsModel = "";
    itsSudo = "";
    itsUSBdevices = "";
}
