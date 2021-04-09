#include <Arduino.h>
#include "optical_encoder.hpp"

// IO DEFINITION
// Analog
// Joystick
uint8_t VR_Y_PIN = A0;
uint8_t VR_X_PIN = A1;

// Digital
// optical relative position
uint8_t LEFT_OPTICAL_A = 2;
uint8_t LEFT_OPTICAL_B = 4;

// Power moter management board
uint8_t LEFT_MOTOR_A = 4;
uint8_t LEFT_MOTOR_B = 5;
uint8_t LEFT_MOTOR_PWM = 6;

int VRx = 0;
int VRy = 0;

// Variables will change:
int ledState = LOW; // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last time LED was updated

// constants won't change:
const long interval = 100; // interval at which to blink (milliseconds)

OpticalEncoder LeftEncoder;

void left_optical_interrupt()
{
    LeftEncoder.update();
}


void setup()
{
    // update display
    pinMode(LED_BUILTIN, OUTPUT);

    LeftEncoder.begin(LEFT_OPTICAL_A, LEFT_OPTICAL_B, 360*2);
    attachInterrupt(digitalPinToInterrupt(LEFT_OPTICAL_A), left_optical_interrupt, RISING);

    Serial.begin(9600);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        // read joystick
        VRy = analogRead(VR_Y_PIN);
        VRx = analogRead(VR_X_PIN);

        Serial.print("Joystick : ");
        Serial.print(VRx);
        Serial.print(", ");
        Serial.print(VRy);
        Serial.print(", ");
        Serial.print(LeftEncoder.get());
        Serial.print("\n");

        // -------- timing ajust ----------------
        // save the last time you blinked the LED
        previousMillis = currentMillis;

        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW)
        {
            ledState = HIGH;
        }
        else
        {
            ledState = LOW;
        }

        // set the LED with the ledState of the variable:
        digitalWrite(LED_BUILTIN, ledState);
    }
}