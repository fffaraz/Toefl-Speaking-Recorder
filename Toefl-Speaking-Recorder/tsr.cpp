#include "tsr.h"

TSR::TSR(QObject *parent) :
    QObject(parent)
{
    ts = TS_STOPPED;
    connect(this, SIGNAL(queueProcess()), this, SLOT(process()), Qt::QueuedConnection);
}

void TSR::start(InputQ _iq)
{
    iq = _iq;

    if(false) return;
    else if(iq.Q1E)
        ts = TS_Q1P;
    else if(iq.Q2E)
        ts = TS_Q2P;
    else if(iq.Q3E)
        ts = TS_Q2P;
    else if(iq.Q4E)
        ts = TS_Q2P;
    else if(iq.Q5E)
        ts = TS_Q2P;
    else if(iq.Q6E)
        ts = TS_Q2P;

    emit queueProcess();
}

void TSR::stop()
{
    ts = TS_STOPPED;
}

void TSR::skip()
{

}

bool TSR::isStarted()
{
    return ts != TS_STOPPED;
}

int TSR::getState()
{
    return ts;
}

void TSR::process()
{
    switch (ts)
    {
    case TS_Q1P:
        syncedPlay(":/sounds/prep.wav");
        syncedPlay(":/sounds/beep.wav");
        break;

    default:
        qDebug() << "TSR::process -> default!";
        break;
    }
}

void TSR::syncedPlay(QString file)
{
    QSound s(file);
    s.play();
    while(!s.isFinished()) QCoreApplication::processEvents();
}
