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
    void start(InputQ _iq);
    void stop();
    void skip();
    bool isStarted();
    int  getState();

private:
    QTime time;
    TIMER_STATE ts;
    InputQ iq;

private slots:
    void syncedPlay(QString file);
    void process();

signals:
    void queueProcess();

public slots:


};

#endif // TSR_H
