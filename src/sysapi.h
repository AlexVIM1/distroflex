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
    SysAPI(QString cmd);
    ~SysAPI(); 
private:
    QProcess itsProc;
    QString itsCmd;
};

#endif // SYSAPI_H
