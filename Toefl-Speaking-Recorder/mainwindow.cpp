#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isStarted = false;
    ui->btnStart->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_btnStart_clicked()
{
    if(!isStarted)
    {
        if(!checkAtleast()) return;
        isStarted = true;
        ui->btnSkip->setEnabled(true);
        ui->btnStart->setText("Stop");
    }
    else
    {
        isStarted = false;
        ui->btnSkip->setEnabled(false);
        ui->btnStart->setText("Start");
    }
}

bool MainWindow::checkAtleast()
{
    if(!ui->chkQ1->isChecked() &&
       !ui->chkQ2->isChecked() &&
       !ui->chkQ3->isChecked() &&
       !ui->chkQ4->isChecked() &&
       !ui->chkQ5->isChecked() &&
       !ui->chkQ6->isChecked()
      )
    {
        QMessageBox alarm;
        alarm.setWindowTitle("Warning");
        alarm.setIcon(QMessageBox::Warning);
        alarm.setText("You need to enable at least one question!");
        alarm.exec();
        return false;
    }
    return true;
}
