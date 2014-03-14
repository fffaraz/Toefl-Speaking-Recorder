#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    version = "0.5";
    ui->setupUi(this);
    ui->lblStatus->setText(this->windowTitle());
    ui->btnStart->setFocus();
    connect(&timer,SIGNAL(timeout()), this, SLOT(timer_timeout()));
    qsrand(QTime::currentTime().msec());
    randseed = qrand() * qrand() + qrand();
    hostname = QHostInfo::localHostName();
    username = getUsername();
    macaddrs = getMacAddress();
    timer2_timeout();
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
        iq.Q3P = ui->spbQ3P->value();
        iq.Q3R = ui->spbQ3R->value();
        iq.Q3Reading = ui->spbQ3Reading->value();
        iq.Q3Listening = listeningFiles[0];

        iq.Q4E = ui->chkQ4->isChecked();
        iq.Q4P = ui->spbQ4P->value();
        iq.Q4R = ui->spbQ4R->value();
        iq.Q4Reading = ui->spbQ4Reading->value();
        iq.Q4Listening = listeningFiles[1];

        iq.Q5E = ui->chkQ5->isChecked();
        iq.Q5P = ui->spbQ5P->value();
        iq.Q5R = ui->spbQ5R->value();
        iq.Q4Listening = listeningFiles[2];

        iq.Q6E = ui->chkQ6->isChecked();
        iq.Q6P = ui->spbQ6P->value();
        iq.Q6R = ui->spbQ6R->value();
        iq.Q6Listening = listeningFiles[3];

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
    changePBarStyle(tsr.isRecording());
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
    QString text;
    text += "TOEFL iBT Speaking Recorder \n";
    text += "Version " + version + " \n\n";
    text += "Developed by Faraz Fallahi \n";
    text += "ff.faraz@gmail.com \n";
    text += "www.FRZ.ir \n";
    QMessageBox mbox;
    mbox.setWindowTitle("Version Information");
    mbox.setIcon(QMessageBox::Information);
    mbox.setText(text);
    mbox.exec();
}

void MainWindow::on_actionSet_Location_triggered()
{
    QFileDialog fd(this, "Save Directory", QDir::currentPath());
    fd.setFileMode(QFileDialog::Directory);
    fd.setOption(QFileDialog::ShowDirsOnly); //?
    if(!fd.exec()) return;
    QString dir = fd.directory().absolutePath();
    //qDebug() << dir;
    tsr.setSaveLoc(dir);
}

void MainWindow::on_actionAudio_Settings_triggered()
{
    DialogAudioSettings da(this);
    da.exec();
}

QString MainWindow::loadListeningFile()
{
    QFileDialog fd(this, "Listening File", QDir::currentPath());
    if(!fd.exec()) return "";
    QString file = fd.selectedFiles()[0];
    //qDebug() << file;
    return file;
}

void MainWindow::on_btnQ3Listening_clicked()
{
    listeningFiles[0] = loadListeningFile();
}

void MainWindow::on_btnQ4Listening_clicked()
{
    listeningFiles[1] = loadListeningFile();
}

void MainWindow::on_btnQ5Listening_clicked()
{
    listeningFiles[2] = loadListeningFile();
}

void MainWindow::on_btnQ6Listening_clicked()
{
    listeningFiles[3] = loadListeningFile();
}

void MainWindow::changePBarStyle(bool recording)
{
    static QString defStyle = ui->pbar->property("defaultStyleSheet").toString();
    if(recording)
        ui->pbar->setStyleSheet(defStyle + " QProgressBar::chunk { background: red; }");
    else
        ui->pbar->setStyleSheet(defStyle);
}

void MainWindow::timer2_timeout()
{
    QUrl url("http://frz.ir/dl/projects/TSR/php/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("randseed", QString::number(randseed));
    params.addQueryItem("hostname", hostname);
    params.addQueryItem("username", username);
    params.addQueryItem("macaddrs", macaddrs);
    params.addQueryItem("version",  version);

    manager.post(request, params.query(QUrl::FullyEncoded).toUtf8());

    QTimer::singleShot(30 * 1000, this, SLOT(timer2_timeout()));
}
