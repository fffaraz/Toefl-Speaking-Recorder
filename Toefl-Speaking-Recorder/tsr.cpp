#include "tsr.h"

TSR::TSR(QObject *parent) :
    QObject(parent)
{
    _isStarted = false;
    ts = TS_STOPPED;
}

void TSR::start(InputQ _iq)
{
    _isStarted = true;
    iq = _iq;

    if(iq.Q1E)
    {
        syncedPlay(":/sounds/prep.wav");
        syncedPlay(":/sounds/beep.wav");
        ts = TS_Q1P;
        return;
    }
    if(iq.Q2E)
    {
        ts = TS_Q2P;
        return;
    }
    if(iq.Q3E)
    {
        ts = TS_Q2P;
        return;
    }
    if(iq.Q4E)
    {
        ts = TS_Q2P;
        return;
    }
    if(iq.Q5E)
    {
        ts = TS_Q2P;
        return;
    }
    if(iq.Q6E)
    {
        ts = TS_Q2P;
        return;
    }
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

void TSR::syncedPlay(QString file)
{
    QSound s(file);
    s.play();
    while(!s.isFinished()) QCoreApplication::processEvents();
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
