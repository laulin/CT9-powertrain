#include "timer.hpp"
#include <limits.h>



void Timer::begin()
{
    this->previous_time = millis();
}


void Timer::update(void)
{
    this->previous_time = millis();
}

unsigned long Timer::get_delta(void)
{
    unsigned long current_time = millis();
    if (current_time > this->previous_time)
    {
        return current_time - this->previous_time;
    }
    else // edge case : counter overflow
    {
        return ULONG_MAX - this->previous_time + current_time;
    }

}