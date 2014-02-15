#ifndef TSR_H
#define TSR_H

#include <QObject>
#include <QtCore>
#include <QtMultimedia>

struct InputQ
{
    bool Q1E;
    int  Q1P;
    int  Q1R;

    bool Q2E;
    int  Q2P;
    int  Q2R;

    bool Q3E;
    bool Q4E;
    bool Q5E;
    bool Q6E;
};

enum TIMER_STATE
{
    TS_STOPPED,
    TS_STARTED,
    TS_Q1P,
    TS_Q1R,
    TS_Q2P,
    TS_Q2R,

};

class TSR : public QObject
{
    Q_OBJECT
public:
    explicit TSR(QObject *parent = 0);
    void start(InputQ _iq);
    void stop();
    void skip();
    bool isStarted();



private:
    QTime time;
    TIMER_STATE ts;
    bool _isStarted;
    InputQ iq;
    void syncedPlay(QString file);

signals:

public slots:

};

#endif // TSR_H
