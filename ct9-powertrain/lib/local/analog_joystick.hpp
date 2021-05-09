#ifndef ANALOG_JOYSTICK_H
#define ANALOG_JOYSTICK_H

#include "Arduino.h"
#include <avr/pgmspace.h>

class AnalogJoystick
{
    private:
        uint8_t pin_x;
        uint8_t pin_y;
        int16_t x;
        int16_t y;
 
    public :
        void begin(uint8_t, uint8_t);
        // to be called to catch joystick position
        void update(void);
        int16_t transform_ADC(int16_t value);

        int16_t transform_to_left_track(int16_t x, int16_t y);
        int16_t transform_to_right_track(int16_t x, int16_t y);

        int16_t get_left_track(void);
        int16_t get_right_track(void);

        int16_t get_x(void);
        int16_t get_y(void);
};

#endif