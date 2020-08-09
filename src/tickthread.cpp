#include "tickthread.h"

tickThread::tickThread(QString cmd, QString cmdClock, int time, QWidget *nowSession, QWidget *sessionCPU, QLabel *output, QLabel *outputClock) :
    itsCmd(cmd),
    itsCmdClock(cmdClock),
    itsTime(time),
    itsNowSession(nowSession),
    itsSessionCPU(sessionCPU),
    itsOutput(output),
    itsOutputClock(outputClock)
{

}

tickThread::~tickThread()
{
    delete itsNowSession;
    delete itsSessionCPU;
    delete itsOutput;
    delete itsOutputClock;
}

void tickThread::run() {
    while (itsNowSession == itsSessionCPU) {

        // Getting core temperature

        itsProc = new SysAPI(itsCmd);
        itsOutput->setText(itsProc->cat()->readAll());

        // Getting CPU clock

        itsProc = new SysAPI(itsCmdClock);
        itsOutputClock->setText(itsProc->cat()->readAll());

        std::this_thread::sleep_for(std::chrono::milliseconds(itsTime));
    }
}
