#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include "dialogabout.h"
#include "dialogaudiosettings.h"
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
    void on_actionVersion_triggered();
    void on_actionSet_Location_triggered();
    void on_actionAudio_Settings_triggered();

    void on_btnStart_clicked();
    void on_btnSkip_clicked();
    void timer_timeout();

    void on_btnQ3Listening_clicked();
    void on_btnQ4Listening_clicked();
    void on_btnQ5Listening_clicked();
    void on_btnQ6Listening_clicked();

private:
    Ui::MainWindow *ui;
    TSR tsr;
    QTimer timer;
    QString listeningFiles[4];
    bool checkAtleast();
    void updateUI(bool state);
    QString loadListeningFile();
};

#endif // MAINWINDOW_H
