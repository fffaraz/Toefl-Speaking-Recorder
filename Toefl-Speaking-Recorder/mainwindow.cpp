#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lblStatus->setText(this->windowTitle());
    ui->btnStart->setFocus();
    connect(&timer,SIGNAL(timeout()), this, SLOT(timer_timeout()));
    timer.start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    //QMessageBox::aboutQt(this);
    DialogAbout da(this);
    da.exec();
}

void MainWindow::on_btnStart_clicked()
{
    if(!tsr.isStarted())
    {
        if(!checkAtleast()) return;
        updateUI(false);
        InputQ iq;

        iq.Q1E = ui->chkQ1->isChecked();
        iq.Q1P = ui->spbQ1P->value();
        iq.Q1R = ui->spbQ1R->value();

        iq.Q2E = ui->chkQ2->isChecked();
        iq.Q2P = ui->spbQ2P->value();
        iq.Q2R = ui->spbQ2R->value();

        tsr.start(iq);
    }
    else
    {
        tsr.stop();
        updateUI(true);
    }
}

void MainWindow::timer_timeout()
{
    // update UI
}

void MainWindow::updateUI(bool state)
{
    if(!state)
    {
        ui->btnSkip->setEnabled(true);
        ui->btnStart->setText("Stop");
        ui->groupBox_1->setEnabled(false);
        ui->groupBox_2->setEnabled(false);
        ui->groupBox_3->setEnabled(false);
        ui->groupBox_4->setEnabled(false);
        ui->groupBox_5->setEnabled(false);
        ui->groupBox_6->setEnabled(false);
    }
    else
    {
        ui->btnSkip->setEnabled(false);
        ui->btnStart->setText("Start");
        ui->groupBox_1->setEnabled(true);
        ui->groupBox_2->setEnabled(true);
        ui->groupBox_3->setEnabled(true);
        ui->groupBox_4->setEnabled(true);
        ui->groupBox_5->setEnabled(true);
        ui->groupBox_6->setEnabled(true);
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


void MainWindow::on_btnSkip_clicked()
{
    tsr.skip();
}
