#include "tsr.h"

TSR::TSR(QObject *parent) :
    QObject(parent)
{
    memset(finishedQ, 0, sizeof(finishedQ));
    ts = TS_STOPPED;
    inProcess = false;
    elapsedTime = 0;
    totalTime = 0;

    saveLoc  = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation); //QDir::currentPath();
    saveLoc += "/";
    //qDebug() << "Default saveLoc" << saveLoc;

    QAudioEncoderSettings audioSettings;
    //audioSettings.setBitRate();
    audioSettings.setChannelCount(1);
    //audioSettings.setCodec("audio/amr");
    //audioSettings.setEncodingMode(QMultimedia::ConstantBitRateEncoding);
    //audioSettings.setQuality(QMultimedia::HighQuality);
    //audioSettings.setSampleRate(16000);

    audioRecorder = new QAudioRecorder;
    audioRecorder->setEncodingSettings(audioSettings);
    //audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());
    //audioRecorder->setAudioInput(audioRecorder->audioInputs()[0]);
    audioRecorder->setVolume(1.0);

    connect(this, SIGNAL(queueProcess()), this, SLOT(process()), Qt::QueuedConnection);
    connect(&timer, SIGNAL(timeout()), this, SLOT(process()));
    timer.start(250);
}

TSR::~TSR()
{
    audioRecorder->deleteLater();
}

void TSR::syncedPlay1(QString file)
{
    QSound s(file);
    s.play();
    while(!s.isFinished())
    {
        QCoreApplication::processEvents();
        QThread::msleep(20);
    }
    elapsedTime = 0; totalTime = 0;
}

void TSR::syncedPlay2(QString file)
{
    TIMER_STATE ts2 = ts;

    QMediaPlayer player;
    player.setMedia(QUrl::fromLocalFile(file));
    player.play();

    totalTime = player.duration() / 1000;
    time.start();

    while(player.state() == QMediaPlayer::PlayingState)
    {
        totalTime = player.duration() / 1000;
        elapsedTime = player.position() / 1000;
        QCoreApplication::processEvents();
        if(ts == TS_STOPPED) break;
        if(ts != ts2) break;
        QThread::msleep(20);
    }

    elapsedTime = 0; totalTime = 0;
}

void TSR::setSaveLoc(QString loc)
{
    saveLoc = loc + "/";
}

void TSR::getSaveLoc()
{
    return saveLoc;
}

void TSR::start(InputQ iq)
{
    memset(finishedQ, 0, sizeof(finishedQ));
    elapsedTime = 0; totalTime = 0;
    time.start();
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
    if(ts == TS_Q1Rf || ts == TS_Q2Rf || ts == TS_Q3Rf || ts == TS_Q4Rf || ts == TS_Q5Rf || ts == TS_Q6Rf) return;
    ts = (TIMER_STATE)( (int)ts + 1 );
}

void TSR::reset()
{
    time.start();
    if(ts == TS_Q3Listen || ts == TS_Q4Listen || ts == TS_Q5Listen || ts == TS_Q6Listen)
        ts = (TIMER_STATE)( (int)ts - 1 );
}

bool TSR::isStarted()
{
    return ts != TS_STOPPED;
}

bool TSR::isRecording()
{
    return audioRecorder->state() == QMediaRecorder::RecordingState;
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
        ts = TS_Q3Readp;
    else if(iq.Q4E && !finishedQ[3])
        ts = TS_Q4Readp;
    else if(iq.Q5E && !finishedQ[4])
        ts = TS_Q5Listen;
    else if(iq.Q6E && !finishedQ[5])
        ts = TS_Q6Listen;
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
        if(iq.Q1P == 0)
        {
            ts = TS_Q1Rp;
            break;
        }
        strState = "Question 1 Preparation";
        ts = TS_Q1Pt;
        //syncedPlay1(":/sounds/q1.wav");
        syncedPlay1(":/sounds/prep.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q1P;
        time.start();
        break;

    case TS_Q1Pt:
        strState = "Question 1 Preparation Time";
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q1Rp;
        break;

    case TS_Q1Rp:
        strState = "Question 1 Response";
        ts = TS_Q1Rt;
        syncedPlay1(":/sounds/speak.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q1R;
        time.start();
        //START RECORDING
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(saveLoc + iq.name + "-Q1"));
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
        syncedPlay1(":/sounds/beep.wav");
        //STOP RECORDING
        audioRecorder->stop();
        break;

    case TS_Q2Pp:
        if(iq.Q2P == 0)
        {
            ts = TS_Q2Rp;
            break;
        }
        strState = "Question 2 Preparation";
        ts = TS_Q2Pt;
        //syncedPlay1(":/sounds/q2.wav");
        syncedPlay1(":/sounds/prep.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q2P;
        time.start();
        break;

    case TS_Q2Pt:
        strState = "Question 2 Preparation Time";
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q2Rp;
        break;

    case TS_Q2Rp:
        strState = "Question 2 Response";
        ts = TS_Q2Rt;
        syncedPlay1(":/sounds/speak.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q2R;
        time.start();
        //START RECORDING
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(saveLoc + iq.name + "-Q2"));
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
        syncedPlay1(":/sounds/beep.wav");
        //STOP RECORDING
        audioRecorder->stop();
        break;

    case TS_Q3Readp:
        if(iq.Q3Reading == 0)
        {
            ts = TS_Q3Listen;
            break;
        }
        strState = "Question 3 Reading";
        ts = TS_Q3Readt;
        //syncedPlay1(":/sounds/q3.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q3Reading;
        time.start();
        break;

    case TS_Q3Readt:
        strState = "Question 3 Reading Time";
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q3Listen;
        break;

    case TS_Q3Listen_S:
        ts = TS_Q3Listen;

    case TS_Q3Listen:
        strState = "Question 3 Listening";
        if(iq.Q3Listening != "") syncedPlay2(iq.Q3Listening);
        if(ts == TS_STOPPED) break;
        if(ts == TS_Q3Listen) ts = TS_Q3Pp;
        break;

    case TS_Q3Pp:
        if(iq.Q3P == 0)
        {
            ts = TS_Q3Rp;
            break;
        }
        strState = "Question 3 Preparation";
        ts = TS_Q3Pt;
        syncedPlay1(":/sounds/prep.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q3P;
        time.start();
        break;

    case TS_Q3Pt:
        strState = "Question 3 Preparation Time";
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q3Rp;
        break;

    case TS_Q3Rp:
        strState = "Question 3 Response";
        ts = TS_Q3Rt;
        syncedPlay1(":/sounds/speak.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q3R;
        time.start();
        //START RECORDING
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(saveLoc + iq.name + "-Q3"));
        audioRecorder->record();
        break;

    case TS_Q3Rt:
        strState = "Question 3 Response Time";
        //RECORDING
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q3Rf;
        break;

    case TS_Q3Rf:
        strState = "Question 3 Response Finished";
        finishedQ[2] = true;
        findNextQ();
        syncedPlay1(":/sounds/beep.wav");
        //STOP RECORDING
        audioRecorder->stop();
        break;

    case TS_Q4Readp:
        if(iq.Q4Reading == 0)
        {
            ts = TS_Q4Listen;
            break;
        }
        strState = "Question 4 Reading";
        ts = TS_Q4Readt;
        //syncedPlay1(":/sounds/q4.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q4Reading;
        time.start();
        break;

    case TS_Q4Readt:
        strState = "Question 4 Reading Time";
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q4Listen;
        break;

    case TS_Q4Listen_S:
        ts = TS_Q4Listen;

    case TS_Q4Listen:
        strState = "Question 4 Listening";
        if(iq.Q4Listening != "") syncedPlay2(iq.Q4Listening);
        if(ts == TS_STOPPED) break;
        if(ts == TS_Q4Listen) ts = TS_Q4Pp;
        break;

    case TS_Q4Pp:
        if(iq.Q4P == 0)
        {
            ts = TS_Q4Rp;
            break;
        }
        strState = "Question 4 Preparation";
        ts = TS_Q4Pt;
        syncedPlay1(":/sounds/prep.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q4P;
        time.start();
        break;

    case TS_Q4Pt:
        strState = "Question 4 Preparation Time";
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q4Rp;
        break;

    case TS_Q4Rp:
        strState = "Question 4 Response";
        ts = TS_Q4Rt;
        syncedPlay1(":/sounds/speak.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q4R;
        time.start();
        //START RECORDING
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(saveLoc + iq.name + "-Q4"));
        audioRecorder->record();
        break;

    case TS_Q4Rt:
        strState = "Question 4 Response Time";
        //RECORDING
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q4Rf;
        break;

    case TS_Q4Rf:
        strState = "Question 4 Response Finished";
        finishedQ[3] = true;
        findNextQ();
        syncedPlay1(":/sounds/beep.wav");
        //STOP RECORDING
        audioRecorder->stop();
        break;

    case TS_Q5Listen_S:
        ts = TS_Q5Listen;

    case TS_Q5Listen:
        strState = "Question 5 Listening";
        //syncedPlay1(":/sounds/beep.wav");
        if(iq.Q5Listening != "") syncedPlay2(iq.Q5Listening);
        if(ts == TS_STOPPED) break;
        if(ts == TS_Q5Listen) ts = TS_Q5Pp;
        break;

    case TS_Q5Pp:
        if(iq.Q5P == 0)
        {
            ts = TS_Q5Rp;
            break;
        }
        strState = "Question 5 Preparation";
        ts = TS_Q5Pt;
        syncedPlay1(":/sounds/prep.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q5P;
        time.start();
        break;

    case TS_Q5Pt:
        strState = "Question 5 Preparation Time";
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q5Rp;
        break;

    case TS_Q5Rp:
        strState = "Question 5 Response";
        ts = TS_Q5Rt;
        syncedPlay1(":/sounds/speak.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q5R;
        time.start();
        //START RECORDING
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(saveLoc + iq.name + "-Q5"));
        audioRecorder->record();
        break;

    case TS_Q5Rt:
        strState = "Question 5 Response Time";
        //RECORDING
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q5Rf;
        break;

    case TS_Q5Rf:
        strState = "Question 5 Response Finished";
        finishedQ[4] = true;
        findNextQ();
        syncedPlay1(":/sounds/beep.wav");
        //STOP RECORDING
        audioRecorder->stop();
        break;

    case TS_Q6Listen_S:
        ts = TS_Q6Listen;

    case TS_Q6Listen:
        strState = "Question 6 Listening";
        //syncedPlay1(":/sounds/beep.wav");
        if(iq.Q6Listening != "") syncedPlay2(iq.Q6Listening);
        if(ts == TS_STOPPED) break;
        if(ts == TS_Q6Listen) ts = TS_Q6Pp;
        break;

    case TS_Q6Pp:
        if(iq.Q6P == 0)
        {
            ts = TS_Q6Rp;
            break;
        }
        strState = "Question 6 Preparation";
        ts = TS_Q6Pt;
        syncedPlay1(":/sounds/prep.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q6P;
        time.start();
        break;

    case TS_Q6Pt:
        strState = "Question 6 Preparation Time";
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q6Rp;
        break;

    case TS_Q6Rp:
        strState = "Question 6 Response";
        ts = TS_Q6Rt;
        syncedPlay1(":/sounds/speak.wav");
        syncedPlay1(":/sounds/beep.wav");
        totalTime = iq.Q6R;
        time.start();
        //START RECORDING
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(saveLoc + iq.name + "-Q6"));
        audioRecorder->record();
        break;

    case TS_Q6Rt:
        strState = "Question 6 Response Time";
        //RECORDING
        elapsedTime = time.elapsed() / 1000;
        if(elapsedTime >= totalTime) ts = TS_Q6Rf;
        break;

    case TS_Q6Rf:
        strState = "Question 6 Response Finished";
        finishedQ[5] = true;
        findNextQ();
        syncedPlay1(":/sounds/beep.wav");
        //STOP RECORDING
        audioRecorder->stop();
        break;

    case TS_END:
        ts = TS_STOPPED;
        break;

    default:
        qDebug() << "TSR::process -> default !" << ts;
        break;
    }
    inProcess = false;
}
