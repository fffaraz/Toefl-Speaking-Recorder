#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>

struct InputQ
{
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
    TS_Q1Rf, //finished

    TS_Q2Pp,
    TS_Q2Pt,
    TS_Q2Rp,
    TS_Q2Rt,
    TS_Q2Rf,


};

#endif // STRUCTS_H
