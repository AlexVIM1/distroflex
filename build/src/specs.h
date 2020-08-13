#ifndef SPECS_H
#define SPECS_H

// Structuring specifications of OS

#include <iostream>
#include <QString>
#include <QSettings>

enum PACKMGRS { PACMAN, APT, ZYPPER };

class specs
{
public:
    specs(QString kernel, QString distro, QString de);
    ~specs();
    QString getKernel() const { return itsKernel; }
    QString getDistro() const { return itsDistro; }
    QString getDe() const { return itsDe; }
    void setUSBdevices(QString usb) { itsUSBdevices = usb; }
    QString getUSBdevices() const { return itsUSBdevices; }
    void setCores(QString cores) { itsCores = cores; }
    QString getCores() const { return itsCores; }
    void setThreads(QString threads) { itsThreads = threads; }
    QString getThreads() const { return itsThreads; }
    void setModel(QString model) { itsModel = model; }
    QString getModel() const { return itsModel; }
    void setSudo(QString sudo) { itsSudo = sudo; }
    QString getSudo() const { return itsSudo; }
    void setVideoSettingsButtonAction(QString videoSettingsButtonAction) { itsVideoSettingsButtonAction = videoSettingsButtonAction; }
    QString getVideoSettingsButtonAction() const { return itsVideoSettingsButtonAction; }
    void setPackMgr(PACKMGRS packMgr) { itsPackMgr = packMgr; }
    PACKMGRS getPackMgr() const { return itsPackMgr; }
    specs() { }
private:
    QString itsKernel;
    QString itsDistro;
    QString itsDe;
    QString itsUSBdevices;
    QString itsCores;
    QString itsThreads;
    QString itsModel;
    QString itsSudo;
    QString itsVideoSettingsButtonAction;
    PACKMGRS itsPackMgr;
};

#endif // SPECS_H
