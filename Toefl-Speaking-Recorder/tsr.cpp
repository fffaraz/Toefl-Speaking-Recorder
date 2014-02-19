#include "tsr.h"

TSR::TSR(QObject *parent) :
    QObject(parent)
{
    memset(finishedQ, 0, sizeof(finishedQ));
    ts = TS_STOPPED;
    inProcess = false;
    connect(this, SIGNAL(queueProcess()), this, SLOT(process()), Qt::QueuedConnection);
    connect(&timer, SIGNAL(timeout()), this, SLOT(process()));
    timer.start(500);
}

void TSR::start(InputQ iq)
{
    this->iq = iq;
    findNextQ();
    queueProcess();
}

void TSR::stop()
{
    ts = TS_STOPPED;
}

void TSR::skip()
{
    //TODO
}

bool TSR::isStarted()
{
    return ts != TS_STOPPED;
}

int TSR::getState()
{
    return ts;
}

void TSR::findNextQ()
{
    if(false) return;
    else if(iq.Q1E && !finishedQ[0])
        ts = TS_Q1Pp;
    else if(iq.Q2E && !finishedQ[1])
        ts = TS_Q2Pp;
    else if(iq.Q3E && !finishedQ[2])
        ts = TS_Q2Pp;
    else if(iq.Q4E && !finishedQ[3])
        ts = TS_Q2Pp;
    else if(iq.Q5E && !finishedQ[4])
        ts = TS_Q2Pp;
    else if(iq.Q6E && !finishedQ[5])
        ts = TS_Q2Pp;
    else
        ts = TS_STOPPED;
}

void TSR::process()
{
    if(inProcess) return;
    inProcess = true;
    switch (ts)
    {
    case TS_STOPPED:
        break;

    case TS_Q1Pp:
        //syncedPlay(":/sounds/q1.wav");
        syncedPlay(":/sounds/prep.wav");
        syncedPlay(":/sounds/beep.wav");
        time.start();
        ts = TS_Q1Pt;
        break;

    case TS_Q1Pt:
        if(time.elapsed() / 1000 >= iq.Q1P)
            ts = TS_Q1Rp;
        break;

    case TS_Q1Rp:
        syncedPlay(":/sounds/prep.wav"); //FIXME
        syncedPlay(":/sounds/beep.wav");
        time.start();
        ts = TS_Q1Rt;
        //START RECORDING
        break;

    case TS_Q1Rt:
        //RECORDING
        if(time.elapsed() / 1000 >= iq.Q1R)
            ts = TS_Q1Rf;
        break;

    case TS_Q1Rf:
        syncedPlay(":/sounds/beep.wav");
        //STOP RECORDING
        finishedQ[0] = true;
        findNextQ();
        break;

    default:
        qDebug() << "TSR::process -> default!";
        break;
    }
    inProcess = false;
}

void TSR::syncedPlay(QString file)
{
    QSound s(file);
    s.play();
    while(!s.isFinished()) QCoreApplication::processEvents();
}
