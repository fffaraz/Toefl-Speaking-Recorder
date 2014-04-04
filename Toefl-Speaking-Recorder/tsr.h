#ifndef TSR_H
#define TSR_H

#include <QObject>
#include <QtCore>
#include <QtMultimedia>

#include "structs.h"

class TSR : public QObject
{
    Q_OBJECT

public:
    explicit TSR(QObject *parent = 0);
    ~TSR();
    void start(InputQ iq);
    void stop();
    void skip();
    void reset();
    bool isStarted();
    bool isRecording();
    QString  getState();
    int  getElapsedTime();
    int  getTotalTime();
    void setSaveLoc(QString loc);

private:
    QTime time;
    QTimer timer;
    TIMER_STATE ts;
    InputQ iq;
    QString strState;
    bool inProcess;
    bool finishedQ[6];
    int  elapsedTime;
    int  totalTime;
    QAudioRecorder *audioRecorder;
    QString saveLoc;

private slots:
    void syncedPlay(QString file);
    void findNextQ();
    void process();

signals:
    void queueProcess();

public slots:


};

#endif // TSR_H
