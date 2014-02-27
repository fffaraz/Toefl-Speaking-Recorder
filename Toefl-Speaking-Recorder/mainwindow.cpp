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
}

MainWindow::~MainWindow()
{
    delete ui;
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

        iq.Q3E = ui->chkQ3->isChecked();
        iq.Q4E = ui->chkQ4->isChecked();
        iq.Q5E = ui->chkQ5->isChecked();
        iq.Q6E = ui->chkQ6->isChecked();

        tsr.start(iq);
        if(!timer.isActive()) timer.start(500);
    }
    else
    {
        tsr.stop();
        updateUI(true);
    }
}

void MainWindow::on_btnSkip_clicked()
{
    tsr.skip();
}

void MainWindow::timer_timeout()
{
    // update UI
    if(!tsr.isStarted()) updateUI(true);
    ui->lblStatus->setText(tsr.getState());
    int elspd =tsr.getElapsedTime();
    QString strTime = QString("%1").arg(elspd, 2, 10, QChar('0'));
    ui->lblTime->setText("00:" + strTime);
    if(tsr.getTotalTime() > 0)
    {
        ui->pbar->setMaximum(tsr.getTotalTime());
        ui->pbar->setValue(elspd);
    }
    else
    {
        ui->pbar->setMaximum(1);
        ui->pbar->setValue(0);
    }
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
    if(
            !ui->chkQ1->isChecked() &&
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

void MainWindow::on_actionAbout_triggered()
{
    //QMessageBox::aboutQt(this);
    DialogAbout da(this);
    da.exec();
}

void MainWindow::on_actionVersion_triggered()
{
    QMessageBox mbox;
    mbox.setWindowTitle("Version Information");
    mbox.setIcon(QMessageBox::Information);
    mbox.setText("TOEFL iBT Speaking Recorder \nVersion 0.2 \n\nDeveloped by Faraz Fallahi \nfffaraz@gmail.com \nwww.FRZ.ir");
    mbox.exec();
}

void MainWindow::on_actionSet_Location_triggered()
{
    QFileDialog fd(this, "Save Directory", QDir::currentPath());
    fd.setFileMode(QFileDialog::Directory);
    //fd.setOption(QFileDialog::ShowDirsOnly);
    fd.exec();
    QString dir = fd.directory().absolutePath();
    //qDebug() << dir;
    tsr.setSaveLoc(dir);
}
