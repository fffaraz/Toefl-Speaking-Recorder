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
    void start(InputQ iq);
    void stop();
    void skip();
    bool isStarted();
    int  getState();

private:
    QTime time;
    QTimer timer;
    TIMER_STATE ts;
    InputQ iq;
    volatile bool inProcess;
    bool finishedQ[6];

private slots:
    void syncedPlay(QString file);
    void findNextQ();
    void process();

signals:
    void queueProcess();

public slots:


};

#endif // TSR_H
