#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    version = "0.8";
    ui->setupUi(this);
    ui->lblStatus->setText(this->windowTitle());
    ui->btnStart->setFocus();
    connect(&timer,SIGNAL(timeout()), this, SLOT(timer_timeout()));
    qsrand(QTime::currentTime().msec());
    randseed = qrand() * qrand() + qrand();
    hostname = QHostInfo::localHostName();
    username = getUsername();
    macaddrs = getMacAddress();
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onRequestCompleted(QNetworkReply*)));
    QTimer::singleShot(1000, this, SLOT(timer2_timeout()));
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

        iq.name = QInputDialog::getText(this, "New Practice", "File Name", QLineEdit::Normal, "P1");

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

void MainWindow::on_btnReset_clicked()
{
    tsr.reset();
}

void MainWindow::timer_timeout()
{
    // update UI
    if(!tsr.isStarted()) updateUI(true);
    changePBarStyle(tsr.isRecording());
    ui->lblStatus->setText(tsr.getState());
    int elspd = tsr.getElapsedTime();
    int total = tsr.getTotalTime();
    int remad = total - elspd;
    QString strTime = QString("%1").arg(remad, 2, 10, QChar('0'));
    ui->lblTime->setText("00:" + strTime);
    if(total > 0)
    {
        ui->pbar->setMaximum(total);
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
        ui->btnReset->setEnabled(true);
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
        ui->btnReset->setEnabled(false);
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
    params.addQueryItem("edition", "baqery");

    manager.post(request, params.query(QUrl::FullyEncoded).toUtf8());

    QTimer::singleShot(30 * 1000, this, SLOT(timer2_timeout()));
}

void MainWindow::onRequestCompleted(QNetworkReply *reply)
{
    QString data = reply->readAll();
    QStringList dlist = data.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    if(dlist.size() < 1) return;
    if(dlist[0] != version)
    {
        static bool again0 = true;
        if(again0)
        {
            QString vstr;
            vstr += "New Version Available \n";
            vstr += "\t\t\t\t\n";
            vstr += "Your   version :  " + version  + "\n";
            vstr += "Latest version :  " + dlist[0] + "";
            show_message(vstr, "New Version");
        }
        again0 = false;
    }

    if(dlist.size() < 2) return;
    if(dlist[1] != "")
    {
        static bool again1 = true;
        if(again1) show_message(dlist[1], "Message");
        again1 = false;
    }
}

void MainWindow::on_actionAll_triggered()
{
    bool c = true;
    ui->chkQ1->setChecked(c);
    ui->chkQ2->setChecked(c);
    ui->chkQ3->setChecked(c);
    ui->chkQ4->setChecked(c);
    ui->chkQ5->setChecked(c);
    ui->chkQ6->setChecked(c);
}

void MainWindow::on_actionNone_triggered()
{
    bool c = false;
    ui->chkQ1->setChecked(c);
    ui->chkQ2->setChecked(c);
    ui->chkQ3->setChecked(c);
    ui->chkQ4->setChecked(c);
    ui->chkQ5->setChecked(c);
    ui->chkQ6->setChecked(c);
}

void MainWindow::show_message(QString msg, QString title)
{
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setWindowTitle(title);
    //msgBox.setInformativeText("");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}
