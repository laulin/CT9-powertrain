#ifndef OPTICAL_ENCODER_H
#define OPTICAL_ENCODER_H

#include "Arduino.h" 

class OpticalEncoder
{
    private:
        volatile int counter;
        uint8_t PinA ;
        uint8_t PinB;
        uint16_t step_per_turn;

    public : 
        void begin(uint8_t PinA, uint8_t PinB, uint16_t resolution);
        void update(void);
        void reset(void);
        int get(void);
        uint16_t get_speed(int16_t reference, uint8_t reverse);
};

#endif