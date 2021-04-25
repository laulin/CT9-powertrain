#ifndef SMOOTH_CONTROL_H
#define SMOOTH_CONTROL_H

#include "Arduino.h"

class SmoothControl
{
    private:
        uint16_t previous_value;
        uint16_t max_acceleration;
        uint16_t relax_factor;
 
    public :
        void begin(uint16_t, uint16_t);
        uint16_t update(unsigned long, uint16_t);
};

#endif