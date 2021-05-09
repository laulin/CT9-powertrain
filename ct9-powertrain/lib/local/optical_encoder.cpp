#include "optical_encoder.hpp"

void OpticalEncoder::begin(uint8_t PinA, uint8_t PinB, uint16_t step_per_turn)
{
    this->counter = 0;
    this->PinA = PinA;
    this->PinB = PinB;
    this->step_per_turn = step_per_turn;

    pinMode(PinA, INPUT_PULLUP);
    pinMode(PinB, INPUT_PULLUP);
}

// to be called on Pin A raising
void OpticalEncoder::update(void)
{
    if (digitalRead(this->PinB))
    {
        this->counter++;
    }
    else
    {
        this->counter--;
    }
}

void OpticalEncoder::reset(void)
{
    this->counter = 0;
}

int OpticalEncoder::get(void)
{
    return this->counter;
}

uint16_t OpticalEncoder::get_speed(int16_t reference, uint8_t reverse)
{
    noInterrupts();
    int counter = this->counter;
    this->counter = 0;
    interrupts();
    int factor = 32767 / reference;

    if (counter>= reference)
    {
        counter = reference;
    }

    if (counter <= -reference)
    {
        counter = - reference;
    }

    if (reverse == 0)
    {
        return (uint16_t) ((counter * factor) + 32768);
    }
    else
    {
        return (uint16_t) (0xFFFF - ((counter * factor) + 32768));

    }
}