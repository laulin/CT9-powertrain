#include "motor_driver.hpp"

#define MAX_SETPOINT 1024
#define HALF_SETPOINT 512

void MotorDriver::begin(uint8_t pin_a, uint8_t pin_b, uint8_t pin_pwm, uint8_t pwm_max, uint8_t polarity)
{
    this->pin_a = pin_a;
    this->pin_b = pin_b;
    this->pin_pwm = pin_pwm;
    this->pwm_max = pwm_max;
    this->polarity = polarity;

    pinMode(pin_a, OUTPUT);
    pinMode(pin_b, OUTPUT);
    pinMode(pin_pwm, OUTPUT);

    digitalWrite(this->pin_a, 0);
    digitalWrite(this->pin_b, 0);
    analogWrite(this->pin_pwm, 0);
}

void MotorDriver::set(uint16_t setpoint)
{
    // camp value between 0-1023
    if (setpoint >= MAX_SETPOINT)
    {
        setpoint = MAX_SETPOINT-1;
    }

    // reverse direction
    if (this->polarity)
    {
        setpoint = MAX_SETPOINT - setpoint;
    }

    // forward
    if (setpoint > HALF_SETPOINT)
    {
        digitalWrite(this->pin_a, 1);
        digitalWrite(this->pin_b, 0);

        uint16_t pwm = (setpoint - HALF_SETPOINT) >> 1;
        pwm = (pwm * this->pwm_max) >> 8; // linear limit
        analogWrite(this->pin_pwm, pwm);
    } 
    else if (setpoint < HALF_SETPOINT) // reverse
    {
        digitalWrite(this->pin_a, 0);
        digitalWrite(this->pin_b, 1);

        uint16_t pwm = (HALF_SETPOINT - setpoint) >> 1;
        pwm = (pwm * this->pwm_max) >> 8; // linear limit
        analogWrite(this->pin_pwm, pwm);
    }
    else // stop
    {
        digitalWrite(this->pin_a, 0);
        digitalWrite(this->pin_b, 0);
        analogWrite(this->pin_pwm, 0);
    }
}