#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "dialogabout.h"
#include "tsr.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();
    void on_btnStart_clicked();
    void on_btnSkip_clicked();
    void timer_timeout();

private:
    Ui::MainWindow *ui;
    TSR tsr;
    QTimer timer;
    bool checkAtleast();
    void updateUI(bool state);
};

#endif // MAINWINDOW_H
