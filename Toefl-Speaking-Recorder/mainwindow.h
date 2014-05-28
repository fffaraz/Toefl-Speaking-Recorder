#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QNetworkAccessManager>

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
    void on_actionAll_triggered();
    void on_actionNone_triggered();

    void on_btnStart_clicked();
    void on_btnSkip_clicked();
    void on_btnReset_clicked();

    void timer_timeout();
    void timer2_timeout();

    void on_btnQ3Listening_clicked();
    void on_btnQ4Listening_clicked();
    void on_btnQ5Listening_clicked();
    void on_btnQ6Listening_clicked();

    void onRequestCompleted(QNetworkReply *reply);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    TSR tsr;
    QTimer timer;
    bool isWaiting;
    QString version;
    quint32 randseed;
    QString hostname;
    QString username;
    QString macaddrs;
    QString listeningFiles[4];
    QNetworkAccessManager manager;
    bool checkAtleast();
    void updateUI(bool isStarted);
    QString loadListeningFile();
    void changePBarStyle(bool recording);
    void show_message(QString msg, QString title = "");
    QString newPracticeName();
};

#endif // MAINWINDOW_H
