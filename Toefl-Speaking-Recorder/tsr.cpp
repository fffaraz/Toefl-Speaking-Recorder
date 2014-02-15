#include "tsr.h"

TSR::TSR(QObject *parent) :
    QObject(parent)
{
    _isStarted = false;
    ts = TS_STOPPED;
}

void TSR::start(InputQ iq)
{
    _isStarted = true;
}

void TSR::stop()
{
    _isStarted = false;
}

void TSR::skip()
{

}

bool TSR::isStarted()
{
    return _isStarted;
}

/*
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
*/
