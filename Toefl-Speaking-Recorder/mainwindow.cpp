#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lblStatus->setText(this->windowTitle());
    ui->btnStart->setFocus();

    isStarted = false;
    ts = TS_STOPPED;

    connect(&timer,SIGNAL(timeout()), this, SLOT(timer_timeout()));
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
        updateUI();
        ts = TS_STARTED;
        timer.start(1000);
    }
    else
    {
        isStarted = false;
        ts = TS_STOPPED;
        updateUI();
    }
}

void MainWindow::timer_timeout()
{
    switch(ts)
    {
    case TS_STOPPED:
        ui->lblStatus->setText("Stopped.");
        break;
    case TS_STARTED:
        ui->lblStatus->setText("Started.");
        time.start();
        if(ui->chkQ1->isChecked())
        {
            QSound::play(":/sounds/prep.wav");
            //QSound::play(":/sounds/beep.wav");
            ts = TS_Q1P;
            break;
        }
        if(ui->chkQ2->isChecked()) { ts = TS_Q2P; break; }
        if(ui->chkQ3->isChecked()) { ts = TS_Q1P; break; }
        if(ui->chkQ4->isChecked()) { ts = TS_Q1P; break; }
        if(ui->chkQ5->isChecked()) { ts = TS_Q1P; break; }
        if(ui->chkQ6->isChecked()) { ts = TS_Q1P; break; }
        break;
    case TS_Q1P:
        ui->lblStatus->setText("Q1P");
        ui->lblTime->setText(QString::number(time.elapsed()));
        ui->pbar->setMaximum(ui->spbQ1P->text().toInt());
        ui->pbar->setValue(time.elapsed() / 1000);
        if(time.elapsed()/1000 >= ui->spbQ1P->text().toInt())
        {
            QSound::play(":/sounds/speak.wav");
            //QSound::play(":/sounds/beep.wav");
            time.start();
            ts = TS_Q1R;
        }
        break;
    case TS_Q1R:
        ui->lblStatus->setText("Q1R");
        break;
    case TS_Q2P:
        break;
    case TS_Q2R:
        break;
    default:
        break;
    }
}

void MainWindow::updateUI()
{
    if(isStarted)
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

