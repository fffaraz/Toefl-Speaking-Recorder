#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtMultimedia>
#include <QMainWindow>
#include <QMessageBox>

enum TIMER_STATE
{
    TS_STOPPED,
    TS_STARTED,
    TS_Q1P,
    TS_Q1R,
    TS_Q2P,
    TS_Q2R,

};

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
    void timer_timeout();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    QTime time;
    TIMER_STATE ts;
    bool isStarted;
    bool checkAtleast();
    void updateUI();
};

#endif // MAINWINDOW_H
