#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "Arduino.h" 

class MotorDriver
{
    private:
        uint8_t pin_a;
        uint8_t pin_b;
        uint8_t pin_pwm;
        uint16_t pwm_max;
        uint8_t polarity;


    public :
        void begin(uint8_t pin_a, uint8_t pin_b, uint8_t pin_pwm, uint8_t pwm_max, uint8_t polarity);
        void set(uint16_t setpoint);
};

#endif