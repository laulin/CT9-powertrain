#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include "Arduino.h"
#include <avr/pgmspace.h>

class CurrentSensor
{
    private:
        uint8_t pin_a;
        uint8_t polarity;


    public :
        void begin(uint8_t pin_a, uint8_t polarity);
        uint16_t get_current(void);
        int8_t get_current_ampere(void);
};

#endif