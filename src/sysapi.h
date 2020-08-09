#ifndef SYSAPI_H
#define SYSAPI_H

#include <QProcess>
#include <QLabel>
#include <thread>
#include <QThread>

// Interface to streaming terminal to Qt

class SysAPI : public QProcess
{
public:
    QProcess *cat();
    QProcess *catLimited();
    SysAPI(QString cmd);
    SysAPI(QString cmd, int time);
    ~SysAPI(); 
private:
    QProcess itsProc;
    QString itsCmd;
    int itsTime;
};

#endif // SYSAPI_H
