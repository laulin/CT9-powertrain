#include <Arduino.h>
#include "optical_encoder.hpp"
#include "analog_joystick.hpp"
#include "motor_driver.hpp"
#include "current_sensor.hpp"

// IO DEFINITION
// Analog
// Joystick
uint8_t VR_Y_PIN = A0;
uint8_t VR_X_PIN = A1;

// Digital
// optical relative position
uint8_t LEFT_OPTICAL_A = 2;
uint8_t LEFT_OPTICAL_B = 4;
uint8_t RIGHT_OPTICAL_A = 3;
uint8_t RIGHT_OPTICAL_B = 5;

// Power moter management board
uint8_t LEFT_MOTOR_A = 50;
uint8_t LEFT_MOTOR_B = 52;
uint8_t LEFT_MOTOR_PWM = 6;
#define MOTOR_MAX_SPEED 255

// current sensor
uint8_t LEFT_CURRENT_SENSOR_PIN = A8;

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


AnalogJoystick Joystick;
MotorDriver LeftMotor;
CurrentSensor LeftCurrentSensor;

void setup()
{
    // update display
    pinMode(LED_BUILTIN, OUTPUT);

    LeftEncoder.begin(LEFT_OPTICAL_A, LEFT_OPTICAL_B, 360*2);
    attachInterrupt(digitalPinToInterrupt(LEFT_OPTICAL_A), left_optical_interrupt, RISING);

    Joystick.begin(VR_X_PIN, VR_Y_PIN);
    LeftMotor.begin(LEFT_MOTOR_A, LEFT_MOTOR_B, LEFT_MOTOR_PWM, MOTOR_MAX_SPEED, 0);
    LeftCurrentSensor.begin(LEFT_CURRENT_SENSOR_PIN, 0);

    Serial.begin(115200);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        // read joystick
        Joystick.update();

        uint16_t left_track_setpoint = Joystick.get_left_track();
        uint16_t right_track_setpoint = Joystick.get_right_track();
        uint16_t left_current_value = LeftCurrentSensor.get_current();

        Serial.print("Joystick : (");
        Serial.print(Joystick.get_x());
        Serial.print(", ");
        Serial.print(Joystick.get_y());
        Serial.print("), tracks :(");
        Serial.print(left_track_setpoint);
        Serial.print(", ");
        Serial.print(right_track_setpoint);
        Serial.print("), encoder :(");
        Serial.print(LeftEncoder.get());
        Serial.print("), current :(");
        Serial.print(left_current_value);
        Serial.print(")");
        Serial.print("\n");

        LeftMotor.set(left_track_setpoint);

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