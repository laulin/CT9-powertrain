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