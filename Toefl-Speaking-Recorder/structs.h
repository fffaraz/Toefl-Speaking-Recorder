#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>

struct InputQ
{
    QString name;

    bool Q1E; //Enabled
    int  Q1P; //Prepare
    int  Q1R; //Response

    bool Q2E;
    int  Q2P;
    int  Q2R;

    bool Q3E;
    int     Q3Reading;
    QString Q3Listening;
    int  Q3P;
    int  Q3R;

    bool Q4E;
    int     Q4Reading;
    QString Q4Listening;
    int  Q4P;
    int  Q4R;

    bool Q5E;
    QString Q5Listening;
    int  Q5P;
    int  Q5R;

    bool Q6E;
    QString Q6Listening;
    int  Q6P;
    int  Q6R;
};

enum TIMER_STATE
{
    TS_STOPPED,

    TS_Q1Pp, //Prepare play
    TS_Q1Pt, //Prepare time
    TS_Q1Rp, //Response play
    TS_Q1Rt, //Response time
    TS_Q1Rf, //Response finished

    TS_Q2Pp,
    TS_Q2Pt,
    TS_Q2Rp,
    TS_Q2Rt,
    TS_Q2Rf,

    TS_Q3Readp,  //Reading play
    TS_Q3Readt,  //Reading time
    TS_Q3Listen, //Listening
    TS_Q3Pp,
    TS_Q3Pt,
    TS_Q3Rp,
    TS_Q3Rt,
    TS_Q3Rf,

    TS_Q4Readp,
    TS_Q4Readt,
    TS_Q4Listen,
    TS_Q4Pp,
    TS_Q4Pt,
    TS_Q4Rp,
    TS_Q4Rt,
    TS_Q4Rf,

    TS_Q5Listen,
    TS_Q5Pp,
    TS_Q5Pt,
    TS_Q5Rp,
    TS_Q5Rt,
    TS_Q5Rf,

    TS_Q6Listen,
    TS_Q6Pp,
    TS_Q6Pt,
    TS_Q6Rp,
    TS_Q6Rt,
    TS_Q6Rf,

    TS_END
};

#endif // STRUCTS_H
