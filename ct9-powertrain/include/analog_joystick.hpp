#ifndef ANALOG_JOYSTICK_H
#define ANALOG_JOYSTICK_H

#include "Arduino.h"
#include <avr/pgmspace.h>

class AnalogJoystick
{
    private:
        uint8_t pin_x;
        uint8_t pin_y;
        uint16_t x;
        uint16_t y;
 
    public :
        void begin(uint8_t, uint8_t);
        // to be called to catch joystick position
        void update(void);
        // return value range 0 to 1024
        // 512 means 
        uint16_t get_left_track(void);
        uint16_t get_right_track(void);
};

#endif