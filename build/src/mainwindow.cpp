#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
     QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setting Kernel

    term = new SysAPI("uname -r");
    QString kernel = term->cat()->readAll();

    // Setting DE

    term = new SysAPI("printenv XDG_CURRENT_DESKTOP");
    QString de = term->cat()->readAll();

    // Setting Distro

    term = new SysAPI("lsb_release -is");
    QString distro = term->cat()->readAll();

    // Initializing OS specifications

    OS = new specs(kernel, distro, de);

    // Disabling other widgets

    ui->DEsettings->setVisible(false);
    ui->label_5->setVisible(false);
    ui->sensors->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->cpuModel->setVisible(false);
    ui->label_8->setVisible(false);
    ui->cpuClock->setVisible(false);
    ui->coresLabel->setVisible(false);
    ui->threadsLabel->setVisible(false);
    ui->label_9->setVisible(false);
    ui->usb->setVisible(false);
    ui->label_10->setVisible(false);
    ui->memdev->setVisible(false);
    ui->deviceEditMount->setVisible(false);
    ui->deviceEditMount->setPlaceholderText("Device");
    ui->deviceEditUMount->setVisible(false);
    ui->deviceEditUMount->setPlaceholderText("Device");
    ui->mount->setVisible(false);
    ui->umount->setVisible(false);
    ui->directoryEdit->setVisible(false);
    ui->directoryEdit->setPlaceholderText("Directory");
    ui->mkfs->setVisible(false);
    ui->mkfsEdit->setVisible(false);
    ui->mkfsEdit->setPlaceholderText("Filesystem");
    ui->mkfsDeviceEdit->setVisible(false);
    ui->mkfsDeviceEdit->setPlaceholderText("Device");
    ui->videocon->setVisible(false);
    ui->videocontitle->setVisible(false);
    ui->displayset->setVisible(false);
    ui->displaysettitle->setVisible(false);
    ui->wres->setVisible(false);
    ui->wres->setPlaceholderText("Width resolution");
    ui->hres->setVisible(false);
    ui->hres->setPlaceholderText("Height resolution");
    ui->hz->setVisible(false);
    ui->hz->setPlaceholderText("Refresh rate");
    ui->input->setVisible(false);
    ui->input->setPlaceholderText("Display input");
    ui->changedisp->setVisible(false);
    ui->videosettingbutton->setVisible(false);
    ui->alsatext->setVisible(false);
    ui->alsavol->setVisible(false);
    ui->alsaslider->setVisible(false);
    ui->alsaslider->setMinimum(0);
    ui->alsaslider->setMaximum(100);
    ui->micvol->setVisible(false);
    ui->micslider->setVisible(false);
    ui->micslider->setMinimum(0);
    ui->micslider->setMaximum(100);
    ui->packagestext->setVisible(false);
    ui->packages->setVisible(false);
    ui->searchpackage->setVisible(false);
    ui->searchpackage->setPlaceholderText("Package");
    ui->searchbutton->setVisible(false);
    ui->removepackage->setVisible(false);
    ui->removepackage->setPlaceholderText("Package");
    ui->removebutton->setVisible(false);
    ui->installpackage->setVisible(false);
    ui->installpackage->setPlaceholderText("Package");
    ui->installbutton->setVisible(false);
    ui->upd->setVisible(false);
    ui->connection->setVisible(false);
    ui->connect_to->setVisible(false);
    ui->connect_to->setPlaceholderText("Connect to server and set time");
    ui->start_ping->setVisible(false);
    ui->ping->setVisible(false);
    ui->contime->setVisible(false);
    ui->dhcpcd->setVisible(false);

    // Setting root access

    dialog = new root(OS, term);
    dialog->setModal(true);
    dialog->exec();

    // Starting category is "Distro Specs"

    on_pushButton_5_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;
    delete OS;
    OS = nullptr;
    delete nowSession;
    nowSession = nullptr;
    for(unsigned long i = 0; i < enabledWidgets.size(); i++) {
        delete enabledWidgets[i];
        enabledWidgets[i] = nullptr;
    }
    enabledWidgets.clear();  
}

void MainWindow::hideWidgets() {
    for(unsigned long i = 0; i < enabledWidgets.size(); i++) {
        enabledWidgets[i]->setVisible(false);
    }
    enabledWidgets.clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    // Setting category

    nowSession = ui->pushButton_5;

    // Clear displaying widgets in the configuring panel

    hideWidgets();

    // Setting Kernel

    QString kernel = OS->getKernel();
    ui->kernelName->setText(kernel);
    ui->label_2->setVisible(true);
    ui->kernelName->setVisible(true);
    enabledWidgets.push_back(ui->label_2);
    enabledWidgets.push_back(ui->kernelName);

    // Setting DE

    QString DE = OS->getDe();
    ui->DEname->setText(DE);
    ui->label_3->setVisible(true);
    ui->DEname->setVisible(true);
    enabledWidgets.push_back(ui->label_3);
    enabledWidgets.push_back(ui->DEname);

    // Setting Distro

    QString distro = OS->getDistro();
    ui->distroName->setText(distro);
    ui->label_4->setVisible(true);
    ui->distroName->setVisible(true);
    enabledWidgets.push_back(ui->label_4);
    enabledWidgets.push_back(ui->distroName);
}

void MainWindow::on_pushButton_6_clicked()
{

    // Setting category

    nowSession = ui->pushButton_6;

    // Getting visible widgets

    hideWidgets();
    ui->label_3->setVisible(true);
    ui->DEname->setVisible(true);
    enabledWidgets.push_back(ui->label_3);
    enabledWidgets.push_back(ui->DEname);

    // Initializing KDE System Settings

    if (OS->getDe() == "KDE\n") {
        ui->label_5->setVisible(true);
        ui->DEsettings->setVisible(true);
        enabledWidgets.push_back(ui->label_5);
        enabledWidgets.push_back(ui->DEsettings);
        ui->DEsettings->setText("System Settings");
        QPixmap PlasmaSettingsPixmap(":/icons/plasma-settings-icon.png");
        QIcon PlasmaSettingsIcon(PlasmaSettingsPixmap);
        ui->DEsettings->setIcon(PlasmaSettingsIcon);
        enabledWidgets.push_back(ui->DEsettings);
    }

    // Initializing XFCE System Settings

    if (OS->getDe().toLower() == "xfce\n") {
        ui->label_5->setVisible(true);
        ui->DEsettings->setVisible(true);
        enabledWidgets.push_back(ui->label_5);
        enabledWidgets.push_back(ui->DEsettings);
        ui->DEsettings->setText("XFCE Settings");
        QPixmap XfceSettingsPixmap(":/icons/xfce-icon.png");
        QIcon XfceSettingsIcon(XfceSettingsPixmap);
        ui->DEsettings->setIcon(XfceSettingsIcon);
        enabledWidgets.push_back(ui->DEsettings);
    }

    // Initializing GNOME System Settings

    if (OS->getDe().toLower() == "gnome\n") {
        ui->label_5->setVisible(true);
        ui->DEsettings->setVisible(true);
        enabledWidgets.push_back(ui->label_5);
        enabledWidgets.push_back(ui->DEsettings);
        ui->DEsettings->setText("GNOME Control Center");
        QPixmap GnomeSettingsPixmap(":/icons/gnome-icon.png");
        QIcon GnomeSettingsIcon(GnomeSettingsPixmap);
        ui->DEsettings->setIcon(GnomeSettingsIcon);
        enabledWidgets.push_back(ui->DEsettings);
    }

    // Initializing LXQT System Settings

    if (OS->getDe().toLower() == "lxqt\n") {
        ui->label_5->setVisible(true);
        ui->DEsettings->setVisible(true);
        enabledWidgets.push_back(ui->label_5);
        enabledWidgets.push_back(ui->DEsettings);
        ui->DEsettings->setText("LxQt Settings");
        QPixmap GnomeSettingsPixmap(":/icons/lxqt-icon.png");
        QIcon GnomeSettingsIcon(GnomeSettingsPixmap);
        ui->DEsettings->setIcon(GnomeSettingsIcon);
        enabledWidgets.push_back(ui->DEsettings);
    }
}

void MainWindow::on_DEsettings_clicked()
{

    // Starting DE settings client

    if (OS->getDe().toLower() == "kde\n") {
        term->QProcess::start("systemsettings5");
    }
    if (OS->getDe().toLower() == "lxqt\n") {
        term->QProcess::start("lxqt-config");
    }
    if (OS->getDe().toLower() == "gnome\n") {
        term->QProcess::start("gnome-control-center");
    }
    if (OS->getDe().toLower() == "xfce\n") {
        term->QProcess::start("xfce4-settings-manager");
    }
}

void MainWindow::on_pushButton_10_clicked()
{

    // Setting category

    nowSession = ui->pushButton_10;

    // Getting visible widgets

    hideWidgets();
    ui->label_6->setVisible(true);
    ui->sensors->setVisible(true);
    ui->label_7->setVisible(true);
    ui->cpuModel->setVisible(true);
    ui->label_8->setVisible(true);
    ui->cpuClock->setVisible(true);
    ui->coresLabel->setVisible(true);
    ui->threadsLabel->setVisible(true);
    enabledWidgets.push_back(ui->label_6);
    enabledWidgets.push_back(ui->sensors);
    enabledWidgets.push_back(ui->label_7);
    enabledWidgets.push_back(ui->cpuModel);
    enabledWidgets.push_back(ui->label_8);
    enabledWidgets.push_back(ui->cpuClock);
    enabledWidgets.push_back(ui->coresLabel);
    enabledWidgets.push_back(ui->threadsLabel);

    // Getting CPU info

    term = new SysAPI("lscpu | grep 'Model name'");
    ui->cpuModel->setText(term->cat()->readAll());
    OS->setModel(term->cat()->readAll());

    QString cores;
    QString threads;

    ui->coresLabel->setText("Cores:");
    cores = ui->coresLabel->text();
    term = new SysAPI("nproc");
    cores.append("                                  ");
    cores.append(term->cat()->readAll());
    ui->coresLabel->setText(cores);
    OS->setCores(cores);

    term = new SysAPI("lscpu | grep Thread");
    ui->threadsLabel->setText(term->cat()->readAll());
    OS->setThreads(threads);

    // Getting output temperature and clock

    th = new tickThread("sensors | grep Core", "lscpu | grep -i mhz", 500, nowSession, ui->pushButton_10, ui->sensors, ui->cpuClock);
    th->start();
}

void MainWindow::on_pushButton_7_clicked()
{

    // Settings category

    nowSession = ui->pushButton_7;

    // Getting visible widgets

    hideWidgets();
    ui->label_9->setVisible(true);
    ui->usb->setVisible(true);
    ui->label_10->setVisible(true);
    ui->memdev->setVisible(true);
    ui->deviceEditMount->setVisible(true);
    ui->deviceEditUMount->setVisible(true);
    ui->mount->setVisible(true);
    ui->umount->setVisible(true);
    ui->mkfs->setVisible(true);
    ui->mkfsEdit->setVisible(true);
    ui->directoryEdit->setVisible(true);
    ui->mkfsDeviceEdit->setVisible(true);
    enabledWidgets.push_back(ui->label_9);
    enabledWidgets.push_back(ui->usb);
    enabledWidgets.push_back(ui->label_10);
    enabledWidgets.push_back(ui->memdev);
    enabledWidgets.push_back(ui->deviceEditMount);
    enabledWidgets.push_back(ui->deviceEditUMount);
    enabledWidgets.push_back(ui->mount);
    enabledWidgets.push_back(ui->umount);
    enabledWidgets.push_back(ui->directoryEdit);
    enabledWidgets.push_back(ui->mkfs);
    enabledWidgets.push_back(ui->mkfsEdit);
    enabledWidgets.push_back(ui->mkfsDeviceEdit);

    // Getting USB devices

    term = new SysAPI("lsusb");
    ui->usb->setText(term->cat()->readAll());

    // Getting Memory devices

    term = new SysAPI("df -h");
    ui->memdev->setText(term->cat()->readAll());
}

void MainWindow::on_mount_clicked()
{
    QString dev = ui->deviceEditMount->text();
    QString dir = ui->directoryEdit->text();
    if (dev.isEmpty())
    {
        dev = "null_device";
    }
    if (dir.isEmpty())
    {
        dir = "null_dir";
    }
    term = new SysAPI("echo " + OS->getSudo() + " | sudo -S echo test\n");
    QString exitSudoStd = term->cat()->readAllStandardOutput();
    if (exitSudoStd.isEmpty())
    {
        ui->statusbar->showMessage("Wrong sudo password");
        return;
    }
    if (!exitSudoStd.isEmpty())
    {
        term = new SysAPI("echo " + OS->getSudo() + " | sudo -S umount " + dev);
        ui->statusbar->showMessage("Mounting " + dev + " to " + dir);
        term = new SysAPI("echo " + OS->getSudo() + " | sudo -S mount " + dev + " " + dir + " && echo check");
        QString exitMountStd = term->cat()->readAllStandardOutput();
        if (!exitMountStd.isEmpty())
        {
            ui->statusbar->showMessage(dev + " mounted succesfully");
        }
        if (exitMountStd.isEmpty())
        {
            ui->statusbar->showMessage("Error: " + term->cat()->readAllStandardError());
        }
    }
    term = new SysAPI("df -h");
    ui->memdev->setText(term->cat()->readAll());
}

void MainWindow::on_umount_clicked()
{
    QString dev = ui->deviceEditUMount->text();
    if (dev.isEmpty())
    {
        dev = "null_device";
    }
    ui->statusbar->showMessage("Verifying root");
    term = new SysAPI("echo " + OS->getSudo() + " | sudo -S echo test\n");
    QString exitSudoStd = term->readAllStandardOutput();
    if (exitSudoStd.isEmpty())
    {
        ui->statusbar->showMessage("Wrong sudo password");
        return;
    }
    if (!exitSudoStd.isEmpty())
    {
        ui->statusbar->showMessage("Umounting " + dev);
        term = new SysAPI("echo " + OS->getSudo() + " | sudo -S umount " + dev + " && echo check");
        QString exitMountStd = term->cat()->readAllStandardOutput();
        if (!exitMountStd.isEmpty())
        {
            ui->statusbar->showMessage(dev + " umounted successfully");
        }
        if (exitMountStd.isEmpty())
        {
            ui->statusbar->showMessage("Error:\n" + term->readAllStandardError());
        }
    }
    term = new SysAPI("df -h");
    ui->memdev->setText(term->cat()->readAll());
}

void MainWindow::on_mkfs_clicked()
{
    QString dev = ui->mkfsDeviceEdit->text();
    QString fs = ui->mkfsEdit->text();
    if (dev.isEmpty())
    {
        dev = "null_device";
    }
    if (fs.isEmpty())
    {
        fs = "null_filesystem";
    }
    term = new SysAPI("echo " + OS->getSudo() + " | sudo -S echo test\n");
    QString exitSudoStd = term->cat()->readAllStandardOutput();
    if (exitSudoStd.isEmpty())
    {
        ui->statusbar->showMessage("Wrong sudo password");
        return;
    }
    if (!exitSudoStd.isEmpty())
    {
        confirmOperation = new confirm("Formate " + dev + " to " + fs + "?");
        confirmOperation->setModal(true);
        confirmOperation->exec();
        if (confirmOperation->getResult())
        {
            ui->statusbar->showMessage("Formatting " + dev + " to " + fs);
            term = new SysAPI("echo " + OS->getSudo() + " | sudo -S mkfs." + fs + " " + dev + " && echo check");
            QString exitMountStd = term->cat()->readAllStandardOutput();
            if (!exitMountStd.isEmpty())
            {
                ui->statusbar->showMessage(dev + " formatted " + "to " + fs + " successfully");
            }
            if (exitMountStd.isEmpty())
            {
                ui->statusbar->showMessage("Error:\n" + term->readAllStandardError());
            }
            term = new SysAPI("df -h");
            ui->memdev->setText(term->cat()->readAll());
        }
        if (!confirmOperation->getResult())
        {
            ui->statusbar->showMessage("Cancelled");
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    nowSession = ui->pushButton_3;
    hideWidgets();
    ui->videocon->setVisible(true);
    ui->videocontitle->setVisible(true);
    ui->displayset->setVisible(true);
    ui->displaysettitle->setVisible(true);
    ui->wres->setVisible(true);
    ui->hres->setVisible(true);
    ui->hz->setVisible(true);
    ui->input->setVisible(true);
    ui->changedisp->setVisible(true);
    enabledWidgets.push_back(ui->videocon);
    enabledWidgets.push_back(ui->videocontitle);
    enabledWidgets.push_back(ui->displayset);
    enabledWidgets.push_back(ui->displaysettitle);
    enabledWidgets.push_back(ui->wres);
    enabledWidgets.push_back(ui->hres);
    enabledWidgets.push_back(ui->hz);
    enabledWidgets.push_back(ui->input);
    enabledWidgets.push_back(ui->changedisp);

    term = new SysAPI("lspci | grep VGA");
    ui->videocon->setText(term->cat()->readAll());

    term = new SysAPI("xrandr");
    ui->displayset->setText(term->cat()->readAll());

    term = new SysAPI("nvidia-settings -l");
    if (term->cat()->readAllStandardError().isEmpty())
    {
        ui->videosettingbutton->setText("Nvidia Settings");
        QPixmap nvidiaTempPix(":/icons/nvidia.png");
        QIcon nvidiaTempIcon(nvidiaTempPix);
        ui->videosettingbutton->setIcon(nvidiaTempIcon);
        OS->setVideoSettingsButtonAction("nvidia");
        ui->videosettingbutton->setVisible(true);
        enabledWidgets.push_back(ui->videosettingbutton);
    }
}

void MainWindow::on_changedisp_clicked()
{
    QString wres = ui->wres->text();
    QString hres = ui->hres->text();
    QString hz = ui->hz->text();
    QString input = ui->input->text();
    if (wres.isEmpty())
    {
        wres = "0";
    }
    if (hres.isEmpty())
    {
        hres = "0";
    }
    if (hz.isEmpty())
    {
        hz = "0";
    }
    if (input.isEmpty())
    {
        input = "null";
    }
    term = new SysAPI("xrandr --output " + input + " --mode " + wres + "x" + hres + " --rate " + hz);
    ui->statusbar->showMessage(term->cat()->readAllStandardOutput() + term->cat()->readAllStandardOutput());
    term = new SysAPI("xrandr");
    ui->displayset->setText(term->cat()->readAll());
}

void MainWindow::on_videosettingbutton_clicked()
{
    if (OS->getVideoSettingsButtonAction() == "nvidia")
    {
        term->QProcess::start("nvidia-settings");
    }
}

void MainWindow::on_pushButton_clicked()
{
    nowSession = ui->pushButton;
    hideWidgets();
    bool alsa = false;
    bool pa = false;
    term = new SysAPI("amixer");
    if (!term->cat()->readAll().isEmpty())
    {
        alsa = true;
        ui->alsatext->setVisible(true);
        ui->alsavol->setVisible(true);
        ui->alsaslider->setVisible(true);
        ui->micvol->setVisible(true);
        ui->micslider->setVisible(true);
        enabledWidgets.push_back(ui->alsatext);
        enabledWidgets.push_back(ui->alsavol);
        enabledWidgets.push_back(ui->alsaslider);
        enabledWidgets.push_back(ui->micvol);
        enabledWidgets.push_back(ui->micslider);
    }
    if (alsa)
    {

        // ALSA 'Master' category volume

        term = new SysAPI("amixer sget 'Master' | awk -F'[][]' '{ print $2 }'");
        QString alsaVolume = term->cat()->readAll();
        ui->alsavol->setText("Master volume: " + alsaVolume);
        alsaVolume.remove(QRegExp("[^a-zA-Z\\d\\s]"));
        ui->alsaslider->setValue(alsaVolume.toInt());

        // ALSA 'Rear Mic' category volume

        term = new SysAPI("amixer sget 'Rear Mic' | awk -F'[][]' '{ print $2 }'");
        QString micVolume = term->cat()->readAll();
        ui->micvol->setText("Rear Mic volume: " + micVolume);
        alsaVolume.remove(QRegExp("[^a-zA-Z\\d\\s]"));
        ui->micslider->setValue(alsaVolume.toInt());
    }
}

void MainWindow::on_alsaslider_sliderMoved(int position)
{
    term = new SysAPI("amixer sset 'Master' " + QString::number(position) + "%");
    term->cat();
    term = new SysAPI("amixer sget 'Master' | awk -F'[][]' '{ print $2 }'");
    QString alsaVolume = term->cat()->readAll();
    ui->alsavol->setText("Volume: " + alsaVolume);
}

void MainWindow::on_micslider_sliderMoved(int position)
{
    term = new SysAPI("amixer sset 'Rear Mic' " + QString::number(position) + "%");
    term->cat();
    term = new SysAPI("amixer sget 'Rear Mic' | awk -F'[][]' '{ print $2 }'");
    QString micVolume = term->cat()->readAll();
    ui->micvol->setText("Rear Mic volume: " + micVolume);
}

void MainWindow::on_pushButton_4_clicked()
{
    nowSession = ui->pushButton_4;
    hideWidgets();
    ui->packagestext->setVisible(true);
    ui->packages->setVisible(true);
    ui->searchpackage->setVisible(true);
    ui->searchbutton->setVisible(true);
    ui->removepackage->setVisible(true);
    ui->removebutton->setVisible(true);
    ui->installpackage->setVisible(true);
    ui->installbutton->setVisible(true);
    ui->upd->setVisible(true);
    enabledWidgets.push_back(ui->packagestext);
    enabledWidgets.push_back(ui->packages);
    enabledWidgets.push_back(ui->searchpackage);
    enabledWidgets.push_back(ui->searchbutton);
    enabledWidgets.push_back(ui->removepackage);
    enabledWidgets.push_back(ui->removebutton);
    enabledWidgets.push_back(ui->installpackage);
    enabledWidgets.push_back(ui->installbutton);
    enabledWidgets.push_back(ui->upd);
    term = new SysAPI("pacman -h");
    if (!term->cat()->readAllStandardOutput().isEmpty())
    {
        OS->setPackMgr(PACMAN);
        ui->packagestext->setText("Pacman:");
        term = new SysAPI("pacman -Q");
        ui->packages->setText(term->cat()->readAll());
    }
    term = new SysAPI("apt -h");
    if (!term->cat()->readAllStandardOutput().isEmpty())
    {
        OS->setPackMgr(APT);
        ui->packagestext->setText("APT:");
        term = new SysAPI("apt list --installed");
        ui->packages->setText(term->cat()->readAll());
    }
    term = new SysAPI("zypper packages --installed-only");
    if (!term->cat()->readAllStandardOutput().isEmpty())
    {
        OS->setPackMgr(ZYPPER);
        ui->packagestext->setText("Zypper:");
        term = new SysAPI("zypper packages --installed-only");
        ui->packages->setText(term->cat()->readAll());
    }
}

void MainWindow::on_searchbutton_clicked()
{
    if (OS->getPackMgr() == PACMAN)
    {
        term = new SysAPI("pacman -Q | grep '" + ui->searchpackage->text() + "'");
        ui->packages->setText(term->cat()->readAll());
    }
    if (OS->getPackMgr() == APT)
    {
        term = new SysAPI("apt list --installed | grep '" + ui->searchpackage->text() + "'");
        ui->packages->setText(term->cat()->readAll());
    }
    if (OS->getPackMgr() == ZYPPER)
    {
        term = new SysAPI("zypper packages --installed-only | grep '" + ui->searchpackage->text() + "'");
        ui->packages->setText(term->cat()->readAll());
    }
}

void MainWindow::on_removebutton_clicked()
{
    QString pkg = ui->removepackage->text();
    if (pkg.isEmpty())
    {
        pkg = "null_pkg";
    }
    term = new SysAPI("echo " + OS->getSudo() + " | sudo -S echo test\n");
    QString exitSudoStd = term->cat()->readAllStandardOutput();
    if (exitSudoStd.isEmpty())
    {
        ui->statusbar->showMessage("Wrong sudo password");
        return;
    }
    if (!exitSudoStd.isEmpty())
    {
        confirmOperation = new confirm("Remove " + pkg + "?");
        confirmOperation->setModal(true);
        confirmOperation->exec();
        if (confirmOperation->getResult())
        {
            if (OS->getPackMgr() == PACMAN)
            {
                term = new SysAPI("echo " + OS->getSudo() + " | sudo -S pacman -R " + pkg + " --noconfirm && echo check");
                QString exitPacmanRemoveStd = term->cat()->readAllStandardOutput();
                if (!exitPacmanRemoveStd.isEmpty())
                {
                    ui->statusbar->showMessage(pkg + " successfully removed");
                }
                if (exitPacmanRemoveStd.isEmpty())
                {
                    ui->statusbar->showMessage("Error: " + term->cat()->readAllStandardError());
                }
                term = new SysAPI("pacman -Q");
                ui->packages->setText(term->cat()->readAll());
            }
            if (OS->getPackMgr() == APT)
            {
                term = new SysAPI("echo " + OS->getSudo() + " | sudo -S apt -y remove " + pkg + " && echo check");
                QString exitPacmanRemoveStd = term->cat()->readAllStandardOutput();
                if (!exitPacmanRemoveStd.isEmpty())
                {
                    ui->statusbar->showMessage(pkg + " successfully removed");
                }
                if (exitPacmanRemoveStd.isEmpty())
                {
                    ui->statusbar->showMessage("Error: " + term->cat()->readAllStandardError());
                }
                term = new SysAPI("apt list --installed");
                ui->packages->setText(term->cat()->readAll());
            }
            if (OS->getPackMgr() == ZYPPER)
            {
                term = new SysAPI("echo " + OS->getSudo() + " | sudo -S zypper -n remove " + pkg + " && echo check");
                QString exitPacmanRemoveStd = term->cat()->readAllStandardOutput();
                if (!exitPacmanRemoveStd.isEmpty())
                {
                    ui->statusbar->showMessage(pkg + " successfully removed");
                }
                if (exitPacmanRemoveStd.isEmpty())
                {
                    ui->statusbar->showMessage("Error: " + term->cat()->readAllStandardError());
                }
                term = new SysAPI("zypper packages --installed-only");
                ui->packages->setText(term->cat()->readAll());
            }
        }
        if (!confirmOperation->getResult())
        {
            ui->statusbar->showMessage("Cancelled");
        }
    }
}

void MainWindow::on_installbutton_clicked()
{
    QString pkg = ui->installpackage->text();
    if (pkg.isEmpty())
    {
        pkg = "null_pkg";
    }
    term = new SysAPI("echo " + OS->getSudo() + " | sudo -S echo test\n");
    QString exitSudoStd = term->cat()->readAllStandardOutput();
    if (exitSudoStd.isEmpty())
    {
        ui->statusbar->showMessage("Wrong sudo password");
        return;
    }
    if (!exitSudoStd.isEmpty())
    {
        confirmOperation = new confirm("Install " + pkg + "?");
        confirmOperation->setModal(true);
        confirmOperation->exec();
        if (confirmOperation->getResult())
        {
            if (OS->getPackMgr() == PACMAN)
            {
                term = new SysAPI("echo " + OS->getSudo() + " | sudo -S pacman -S " + pkg + " --noconfirm && echo check");
                QString exitPacmanInstallStd = term->cat()->readAllStandardOutput();
                if (!exitPacmanInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage(pkg + " successfully installed");
                }
                if (exitPacmanInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage("Error: " + term->cat()->readAllStandardError());
                }
                term = new SysAPI("pacman -Q");
                ui->packages->setText(term->cat()->readAll());
            }
            if (OS->getPackMgr() == APT)
            {
                term = new SysAPI("echo " + OS->getSudo() + " | sudo -S apt -y install " + pkg + " && echo check");
                QString exitAptInstallStd = term->cat()->readAllStandardOutput();
                if (!exitAptInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage(pkg + " successfully installed");
                }
                if (exitAptInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage("Error: " + term->cat()->readAllStandardError());
                }
                term = new SysAPI("apt list --installed");
                ui->packages->setText(term->cat()->readAll());
            }
            if (OS->getPackMgr() == ZYPPER)
            {
                term = new SysAPI("echo " + OS->getSudo() + " | sudo -S zypper -n install " + pkg + " && echo check");
                QString exitZypperInstallStd = term->cat()->readAllStandardOutput();
                if (!exitZypperInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage(pkg + " successfully installed");
                }
                if (exitZypperInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage("Error: " + term->cat()->readAllStandardError());
                }
                term = new SysAPI("zypper packages --installed-only");
                ui->packages->setText(term->cat()->readAll());
            }
        }
        if (!confirmOperation->getResult())
        {
            ui->statusbar->showMessage("Cancelled");
        }
    }
}

void MainWindow::on_upd_clicked()
{
    term = new SysAPI("echo " + OS->getSudo() + " | sudo -S echo test\n");
    QString exitSudoStd = term->cat()->readAllStandardOutput();
    if (exitSudoStd.isEmpty())
    {
        ui->statusbar->showMessage("Wrong sudo password");
        return;
    }
    if (!exitSudoStd.isEmpty())
    {
        confirmOperation = new confirm("Update system?");
        confirmOperation->setModal(true);
        confirmOperation->exec();
        if (confirmOperation->getResult())
        {
            if (OS->getPackMgr() == PACMAN)
            {
                term = new SysAPI("echo " + OS->getSudo() + " | sudo -S pacman -Syu --noconfirm && echo check");
                QString exitPacmanInstallStd = term->cat()->readAllStandardOutput();
                if (!exitPacmanInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage("Successfully updated");
                }
                if (exitPacmanInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage("Error: " + term->cat()->readAllStandardError());
                }
                term = new SysAPI("pacman -Q");
                ui->packages->setText(term->cat()->readAll());
            }
            if (OS->getPackMgr() == APT)
            {
                term = new SysAPI("echo " + OS->getSudo() + " | sudo -S apt -y update && sudo apt -y upgrade && echo check");
                QString exitAptInstallStd = term->cat()->readAllStandardOutput();
                if (!exitAptInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage("Successfully updated");
                }
                if (exitAptInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage("Error: " + term->cat()->readAllStandardError());
                }
                term = new SysAPI("apt list --installed");
                ui->packages->setText(term->cat()->readAll());
            }
            if (OS->getPackMgr() == ZYPPER)
            {
                term = new SysAPI("echo " + OS->getSudo() + " | sudo -S zypper -n update && echo check");
                QString exitZypperInstallStd = term->cat()->readAllStandardOutput();
                if (!exitZypperInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage("Successfully updated");
                }
                if (exitZypperInstallStd.isEmpty())
                {
                    ui->statusbar->showMessage("Error: " + term->cat()->readAllStandardError());
                }
                term = new SysAPI("zypper packages --installed-only");
                ui->packages->setText(term->cat()->readAll());
            }
        }
        if (!confirmOperation->getResult())
        {
            ui->statusbar->showMessage("Cancelled");
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    nowSession = ui->pushButton_2;
    hideWidgets();
    ui->connect_to->setVisible(true);
    ui->start_ping->setVisible(true);
    ui->ping->setVisible(true);
    ui->connection->setVisible(true);
    ui->contime->setVisible(true);
    ui->dhcpcd->setVisible(true);
    enabledWidgets.push_back(ui->connection);
    enabledWidgets.push_back(ui->connect_to);
    enabledWidgets.push_back(ui->start_ping);
    enabledWidgets.push_back(ui->ping);
    enabledWidgets.push_back(ui->contime);
    enabledWidgets.push_back(ui->dhcpcd);
    term = new SysAPI("ping 8.8.8.8", 800);
    QString exitPingStd = term->catLimited()->readAllStandardOutput();
    QString result;
    if (exitPingStd.isEmpty())
    {
        result = "no";
    }
    if (!exitPingStd.isEmpty())
    {
        result = "yes";
    }
    ui->connection->setText("Connection: " + result);
}

void MainWindow::on_start_ping_clicked()
{
    QString server = ui->connect_to->text();
    QString time = ui->contime->text();
    if (server.isEmpty())
    {
        server = "null_server";
    }
    term = new SysAPI("ping " + server, time.toInt()*1000);
    ui->ping->setText(term->catLimited()->readAllStandardOutput());
}

void MainWindow::on_dhcpcd_clicked()
{
    term = new SysAPI("echo " + OS->getSudo() + " | sudo -S echo test\n");
    QString exitSudoStd = term->cat()->readAllStandardOutput();
    if (exitSudoStd.isEmpty())
    {
        ui->statusbar->showMessage("Wrong sudo password");
        return;
    }
    if (!exitSudoStd.isEmpty())
    {
        term = new SysAPI("echo " + OS->getSudo() + " | sudo -S dhcpcd && echo check");
        term->cat();
        term = new SysAPI("ping 8.8.8.8", 800);
        QString exitPingStd = term->catLimited()->readAllStandardOutput();
        QString result;
        if (exitPingStd.isEmpty())
        {
            result = "no";
        }
        if (!exitPingStd.isEmpty())
        {
            result = "yes";
        }
        ui->connection->setText("Connection: " + result);
    }
}
