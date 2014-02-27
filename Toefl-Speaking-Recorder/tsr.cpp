#include "tsr.h"

TSR::TSR(QObject *parent) :
    QObject(parent)
{
    memset(finishedQ, 0, sizeof(finishedQ));
    ts = TS_STOPPED;
    inProcess = false;
    elapsedTime = 0;
    totalTime = 0;

    saveLoc = QDir::currentPath();
    audioRecorder = new QAudioRecorder;

    QAudioEncoderSettings audioSettings;
    //audioSettings.setCodec("audio/amr");
    audioSettings.setQuality(QMultimedia::LowQuality);
    audioSettings.setChannelCount(1);
    //audioSettings.setSampleRate();
    //audioSettings.setBitRate();

    audioRecorder->setEncodingSettings(audioSettings);
    //audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());
    //audioRecorder->setAudioInput(audioRecorder->audioInputs()[0]);
    //audioRecorder->setVolume();

    connect(this, SIGNAL(queueProcess()), this, SLOT(process()), Qt::QueuedConnection);
    connect(&timer, SIGNAL(timeout()), this, SLOT(process()));
    timer.start(500);
}

void TSR::syncedPlay(QString file)
{
    QSound s(file);
    s.play();
    while(!s.isFinished()) QCoreApplication::processEvents();
    elapsedTime = 0; totalTime = 0;
}

void TSR::setSaveLoc(QString loc)
{
    saveLoc = loc;
}

void TSR::start(InputQ iq)
{
    memset(finishedQ, 0, sizeof(finishedQ));
    elapsedTime = 0; totalTime = 0;
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
    //FIXME
    //ts=(TIMER_STATE)((int)ts+1);
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
    elapsedTime = 0; totalTime = 0;
    if(false) return;
    else if(iq.Q1E && !finishedQ[0])
        ts = TS_Q1Pp;
    else if(iq.Q2E && !finishedQ[1])
        ts = TS_Q2Pp;
    else if(iq.Q3E && !finishedQ[2])
        ts = TS_STOPPED;
    else if(iq.Q4E && !finishedQ[3])
        ts = TS_STOPPED;
    else if(iq.Q5E && !finishedQ[4])
        ts = TS_STOPPED;
    else if(iq.Q6E && !finishedQ[5])
        ts = TS_STOPPED;
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
        elapsedTime = 0; totalTime = 0;
        audioRecorder->stop();
        break;

    case TS_Q1Pp:
        strState = "Question 1 Prepare Play";
        ts = TS_Q1Pt;
        //syncedPlay(":/sounds/q1.wav");
        syncedPlay(":/sounds/prep.wav");
        syncedPlay(":/sounds/beep.wav");
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
        ts = TS_Q1Rt;
        syncedPlay(":/sounds/speak.wav");
        syncedPlay(":/sounds/beep.wav");
        totalTime = iq.Q1R;
        time.start();
        //START RECORDING
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(saveLoc + "/Q1"));
        audioRecorder->record();
        break;

    case TS_Q1Rt:
        strState = "Question 1 Response Time";
        //RECORDING
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q1Rf;
        break;

    case TS_Q1Rf:
        strState = "Question 1 Response Finished";
        finishedQ[0] = true;
        findNextQ();
        syncedPlay(":/sounds/beep.wav");
        //STOP RECORDING
        audioRecorder->stop();
        break;

    case TS_Q2Pp:
        strState = "Question 2 Prepare Play";
        ts = TS_Q2Pt;
        //syncedPlay(":/sounds/q2.wav");
        syncedPlay(":/sounds/prep.wav");
        syncedPlay(":/sounds/beep.wav");
        totalTime = iq.Q2P;
        time.start();
        break;

    case TS_Q2Pt:
        strState = "Question 2 Prepare Time";
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q2Rp;
        break;

    case TS_Q2Rp:
        strState = "Question 2 Response Play";
        ts = TS_Q2Rt;
        syncedPlay(":/sounds/speak.wav");
        syncedPlay(":/sounds/beep.wav");
        totalTime = iq.Q2R;
        time.start();
        //START RECORDING
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(saveLoc + "/Q2"));
        audioRecorder->record();
        break;

    case TS_Q2Rt:
        strState = "Question 2 Response Time";
        //RECORDING
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q2Rf;
        break;

    case TS_Q2Rf:
        strState = "Question 2 Response Finished";
        finishedQ[1] = true;
        findNextQ();
        syncedPlay(":/sounds/beep.wav");
        //STOP RECORDING
        audioRecorder->stop();
        break;

    default:
        qDebug() << "TSR::process -> default!";
        break;
    }
    inProcess = false;
}
