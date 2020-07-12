#include "tickthread.h"

tickThread::tickThread(QString cmd, QString cmdClock, int time, QWidget *nowSession, QWidget *sessionCPU, QLabel *output, QLabel *outputClock) :
    itsCmd(cmd),
    itsCmdClock(cmdClock),
    itsTime(time),
    itsNowSession(nowSession),
    itsSessionCPU(sessionCPU),
    itsOutput(output),
    fout(new std::ofstream),
    fin(new std::ifstream),
    itsOutputClock(outputClock)
{

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
        itsProc.write(itsCmdClock.toLatin1());
        itsProc.closeWriteChannel();
        itsProc.waitForFinished();
        itsOutputClock->setText(itsProc.readAll());

        std::this_thread::sleep_for(std::chrono::milliseconds(itsTime));
    }
}
