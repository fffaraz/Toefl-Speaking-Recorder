#include "tsr.h"

TSR::TSR(QObject *parent) :
    QObject(parent)
{
    memset(finishedQ, 0, sizeof(finishedQ));
    ts = TS_STOPPED;
    inProcess = false;
    elapsedTime = 0;
    totalTime = 0;
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
    elapsedTime = 0;
    totalTime = 0;
}

void TSR::skip()
{
    //TODO
}

bool TSR::isStarted()
{
    return ts != TS_STOPPED;
}

QString TSR::getState()
{
    return strState;
}

int TSR::getElapsedTime()
{
    return elapsedTime;
}

int TSR::getTotalTime()
{
    return totalTime;
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
        strState = "Stopped";
        break;

    case TS_Q1Pp:
        strState = "Question 1 Prepare Play";
        //syncedPlay(":/sounds/q1.wav");
        syncedPlay(":/sounds/prep.wav");
        syncedPlay(":/sounds/beep.wav");
        ts = TS_Q1Pt;
        totalTime = iq.Q1P;
        time.start();
        break;

    case TS_Q1Pt:
        strState = "Question 1 Prepare Time";
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q1Rp;
        break;

    case TS_Q1Rp:
        strState = "Question 1 Response Play";
        syncedPlay(":/sounds/speak.wav");
        syncedPlay(":/sounds/beep.wav");
        ts = TS_Q1Rt;
        totalTime = iq.Q1R;
        time.start();
        //START RECORDING
        break;

    case TS_Q1Rt:
        strState = "Question 1 Response Time";
        //RECORDING
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q1Rf;
        break;

    case TS_Q1Rf:
        strState = "Question 1 Response Finished";
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
