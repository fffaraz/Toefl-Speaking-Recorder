#ifndef STRUCTS_H
#define STRUCTS_H

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

    TS_Q1Pp, //play
    TS_Q1Pt, //time
    TS_Q1Rp, //play
    TS_Q1Rt, //time
    TS_Q1Rf, //finished

    TS_Q2Pp,
    TS_Q2Pt,
    TS_Q2Rp,
    TS_Q2Rt,
    TS_Q2Rf,
};

#endif // STRUCTS_H
