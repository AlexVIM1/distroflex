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
    ui->patext->setVisible(false);
    ui->pavol->setVisible(false);
    ui->alsaslider->setVisible(false);
    ui->paslider->setVisible(false);

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
    enabledWidgets.clear();

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
}

void MainWindow::on_DEsettings_clicked()
{

    // Starting DE settings client

    if (OS->getDe() == "KDE\n") {
        term->start("systemsettings5");
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
    }
    term = new SysAPI("df -h");
    ui->memdev->setText(term->cat()->readAll());
}

void MainWindow::on_pushButton_3_clicked()
{
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
        term->start("nvidia-settings");
    }
}

void MainWindow::on_pushButton_clicked()
{
    hideWidgets();
    bool alsa = false;
    bool pa = false;
    term = new SysAPI("aplay -l");
    if (!term->cat()->readAll().isEmpty())
    {
        alsa = true;
        ui->alsatext->setVisible(true);
        ui->alsavol->setVisible(true);
        ui->alsaslider->setVisible(true);
        enabledWidgets.push_back(ui->alsatext);
        enabledWidgets.push_back(ui->alsavol);
        enabledWidgets.push_back(ui->alsaslider);
    }
    term = new SysAPI("pactl list");
    if (!term->cat()->readAll().isEmpty())
    {
        pa = true;
        ui->patext->setVisible(true);
        ui->pavol->setVisible(true);
        ui->paslider->setVisible(true);
        enabledWidgets.push_back(ui->patext);
        enabledWidgets.push_back(ui->pavol);
        enabledWidgets.push_back(ui->paslider);
    }

    if (alsa)
    {
        term = new SysAPI("amixer sget Master | awk -F'[][]' '{ print $2 }'");
        QString alsaVolume = term->cat()->readAll();
        ui->alsavol->setText("Volume: " + alsaVolume);
        alsaVolume.remove(QRegExp("[^a-zA-Z\\d\\s]"));
        ui->alsaslider->setValue(alsaVolume.toInt());
    }
    if (pa)
    {
        term = new SysAPI("pactl list sinks | perl -000ne 'if(/#1/){/(Volume:.*)/; print ""$1\n""}'");
        QString paVolume = term->cat()->readAll();

        // pactl already has "Volume: " in line

        ui->pavol->setText(paVolume);
        paVolume.remove(QRegExp("[^a-zA-Z\\d\\s]"));
        ui->statusbar->showMessage(paVolume);
    }
}
