#ifndef TICKTHREAD_H
#define TICKTHREAD_H

#include <QThread>
#include "sysapi.h"
#include <QLabel>
#include <QStatusBar>

// Creating QThread-based class
// Overrriding void run() to base there code

class tickThread : public QThread
{
public:
    void run() override;
    tickThread(QString cmd, QString cmdClock, int time, QWidget *nowSession, QWidget *sessionCPU, QLabel *output, QLabel *outputClock);
    ~tickThread();
private:
    SysAPI *itsProc;
    QString itsCmd;
    QString itsCmdClock;
    int itsTime;
    QWidget *itsNowSession;
    QWidget *itsSessionCPU;
    QLabel *itsOutput;
    QLabel *itsOutputClock;
};

#endif // TICKTHREAD_H
