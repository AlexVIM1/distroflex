#ifndef TICKTHREAD_H
#define TICKTHREAD_H

#include <QThread>
#include <QProcess>
#include <QLabel>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

// Creating QThread-based class
// Overrriding void run() to base there code

class tickThread : public QThread
{
public:
    void run();
    tickThread(QString cmd, char cmdClock[255], int time, QWidget *nowSession, QWidget *sessionCPU, QLabel *output, QLabel *outputClock);
    ~tickThread();
private:
    QProcess itsProc;
    QString itsCmd;
    char itsCmdClock[255];
    int itsTime;
    QWidget *itsNowSession;
    QWidget *itsSessionCPU;
    QLabel *itsOutput;
    QLabel *itsOutputClock;
    std::ofstream *fout;
    std::ifstream *fin;
};

#endif // TICKTHREAD_H
