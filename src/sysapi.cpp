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

QProcess *SysAPI::cat()
{
    itsProc.start("sh");
    itsProc.write(itsCmd.toUtf8());
    itsProc.closeWriteChannel();
    itsProc.waitForFinished();
    return &itsProc;
}
