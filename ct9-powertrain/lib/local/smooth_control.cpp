#include "smooth_control.hpp"

#define HALF_SETPOINT 32767
#define FULL_SETPOINT 65535

void SmoothControl::begin(uint16_t max_acceleration, uint16_t relax_factor)
{
    this->previous_value = HALF_SETPOINT;
    this->max_acceleration = max_acceleration;
    this->relax_factor = relax_factor;
}

uint16_t uint16_no_overflow_add(uint16_t value, uint16_t to_add)
{
    uint16_t output = value + to_add;

    if (output < value)
    {
        return FULL_SETPOINT;
    }
    else
    {
        return output;
    }
}

uint16_t uint16_no_overflow_sub(uint16_t value, uint16_t to_sub)
{
    uint16_t output = value - to_sub;

    if (output > value)
    {
        return 0;
    }
    else
    {
        return output;
    }
}

// delta is the number of millisecond since the last update
uint16_t SmoothControl::update(unsigned long delta, uint16_t setpoint)
{
    uint16_t max_acceleration = (uint16_t) min(FULL_SETPOINT, (uint32_t)this->max_acceleration * (uint32_t)delta);
    uint16_t relax_factor = (uint16_t) min(FULL_SETPOINT, (uint32_t)this->relax_factor * (uint32_t)delta);

    if (this->previous_value > HALF_SETPOINT)
    {
        uint16_t max_range = uint16_no_overflow_add(this->previous_value, max_acceleration);
        uint16_t min_range = uint16_no_overflow_sub(this->previous_value, relax_factor);

        if (setpoint > this->previous_value)
        {
            this->previous_value = uint16_no_overflow_add(this->previous_value, setpoint - this->previous_value);
        }
        else if (setpoint < this->previous_value)
        {
            this->previous_value = uint16_no_overflow_sub(this->previous_value, this->previous_value - setpoint);
        }
        this->previous_value = constrain(this->previous_value, min_range, max_range);
    }
    else // (this->previous_value <= HALF_SETPOINT)
    {
        uint16_t max_range = uint16_no_overflow_add(this->previous_value, relax_factor);
        uint16_t min_range = uint16_no_overflow_sub(this->previous_value, max_acceleration);

        if (setpoint > this->previous_value)
        {
            this->previous_value = uint16_no_overflow_add(this->previous_value, setpoint - this->previous_value);
        }
        else if (setpoint < this->previous_value)
        {
            this->previous_value = uint16_no_overflow_sub(this->previous_value, this->previous_value - setpoint);
        }
        this->previous_value = constrain(this->previous_value, min_range, max_range);
    }

    return this->previous_value;
}

