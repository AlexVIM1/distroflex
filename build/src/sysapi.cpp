#include "sysapi.h"

// Constructor to initialize command data

SysAPI::SysAPI(QString cmd) :
    itsCmd(cmd)
{

}

// Constructor to initialize command data and time

SysAPI::SysAPI(QString cmd, int time) :
    itsCmd(cmd),
    itsTime(time)
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

QProcess *SysAPI::catLimited()
{
    itsProc.start("sh");
    itsProc.write(itsCmd.toUtf8());
    itsProc.closeWriteChannel();
    itsProc.waitForFinished(itsTime);
    return &itsProc;
}
