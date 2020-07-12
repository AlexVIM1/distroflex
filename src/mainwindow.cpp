#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
     QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setting Kernel

    term = new SysAPI("uname -r");
    QString kernel = term->cat();

    // Setting DE

    term = new SysAPI("printenv XDG_CURRENT_DESKTOP");
    QString de = term->cat();

    // Setting Distro

    term = new SysAPI("lsb_release -is");
    QString distro = term->cat();

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

    QString *kernel;
    kernel = new QString;
    *kernel = OS->getKernel();
    ui->kernelName->setText(*kernel);
    ui->label_2->setVisible(true);
    ui->kernelName->setVisible(true);
    enabledWidgets.push_back(ui->label_2);
    enabledWidgets.push_back(ui->kernelName);
    delete kernel;
    kernel = nullptr;

    // Setting DE

    QString *DE;
    DE = new QString;
    *DE = OS->getDe();
    ui->DEname->setText(*DE);
    ui->label_3->setVisible(true);
    ui->DEname->setVisible(true);
    enabledWidgets.push_back(ui->label_3);
    enabledWidgets.push_back(ui->DEname);

    // Setting Distro

    QString *distro;
    distro = new QString;
    *distro = OS->getDistro();
    ui->distroName->setText(*distro);
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
    ui->label_5->setVisible(true);
    ui->DEsettings->setVisible(true);
    enabledWidgets.push_back(ui->label_5);
    enabledWidgets.push_back(ui->DEsettings);

    // Initializing KDE System Settings

    if (OS->getDe() == "KDE\n") {
        ui->DEsettings->setVisible(true);
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
        term->QProcess::start("systemsettings5");
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
    enabledWidgets.push_back(ui->label_6);
    enabledWidgets.push_back(ui->sensors);
    enabledWidgets.push_back(ui->label_7);
    enabledWidgets.push_back(ui->cpuModel);
    enabledWidgets.push_back(ui->label_8);
    enabledWidgets.push_back(ui->cpuClock);

    // Getting CPU info

    term = new SysAPI("");
    term->start("sh");
    term->write("lscpu | grep 'M+odel name'");
    term->closeWriteChannel();
    term->waitForFinished();
    ui->cpuModel->setText(term->readAll());

    // Getting output temperature

    th = new tickThread("sensors | grep Core", "lscpu | grep -i mhz", 500, nowSession, ui->pushButton_10, ui->sensors, ui->cpuClock);
    th->start();
}
