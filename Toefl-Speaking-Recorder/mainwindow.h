#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtMultimedia>
#include <QMainWindow>
#include <QMessageBox>

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

private:
    Ui::MainWindow *ui;
    bool isStarted;
    bool checkAtleast();
};

#endif // MAINWINDOW_H
