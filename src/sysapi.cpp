#include "sysapi.h"

// Constructor to initialize command data

SysAPI::SysAPI(QString cmd) :
    itsCmd(cmd)
{

}

// Deleting command data

SysAPI::~SysAPI()
{
    itsCmd = "";
}

// Streaming command result to user

QByteArray SysAPI::cat()
{
    itsProc.start(itsCmd);
    itsProc.waitForFinished();
    return itsProc.readAll();
}
