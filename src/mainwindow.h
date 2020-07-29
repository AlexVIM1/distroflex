#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <vector>
#include <thread>

#include "sysapi.h"
#include "specs.h"
#include "tickthread.h"
#include "root.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void hideWidgets();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_DEsettings_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_7_clicked();

    void on_mount_clicked();

    void on_umount_clicked();

    void on_mkfs_clicked();

    void on_pushButton_3_clicked();

    void on_changedisp_clicked();

    void on_videosettingbutton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    // Specifications stream channel

    specs *OS;

    // Visible widgets
    // Required to use directories of settings

    std::vector<QWidget*> enabledWidgets;

    // API to using terminal

    SysAPI *term;

    // What category is now active

    QWidget *nowSession;

    // Thread to tick sensors

    tickThread *th;

    // Root dialog

    root *dialog;
};

#endif // MAINWINDOW_H
