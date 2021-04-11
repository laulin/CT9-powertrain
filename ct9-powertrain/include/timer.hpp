#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

class Timer
{
    private:
        unsigned long previous_time;

    public :
        void begin();
        void update(void);
        unsigned long get_delta(void);
};

#endif