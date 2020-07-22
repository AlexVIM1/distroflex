#include "tickthread.h"

tickThread::tickThread(QString cmd, char cmdClock[255], int time, QWidget *nowSession, QWidget *sessionCPU, QLabel *output, QLabel *outputClock) :
    itsCmd(cmd),
    itsTime(time),
    itsNowSession(nowSession),
    itsSessionCPU(sessionCPU),
    itsOutput(output),
    fout(new std::ofstream),
    fin(new std::ifstream),
    itsOutputClock(outputClock)
{
    for (int i = 0; i < 255; i++)
    {
        itsCmdClock[i] = cmdClock[i];
    }
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

        itsProc.start("sh");
        itsProc.write(itsCmd.toLatin1());
        itsProc.closeWriteChannel();
        itsProc.waitForFinished();
        itsOutput->setText(itsProc.readAll());

        // Getting CPU clock

        itsProc.start("sh");
        itsProc.write(itsCmdClock);
        itsProc.closeWriteChannel();
        itsProc.waitForFinished();
        itsOutputClock->setText(itsProc.readAll());

        std::this_thread::sleep_for(std::chrono::milliseconds(itsTime));
    }
}
