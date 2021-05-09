#include <Arduino.h>
#include <unity.h>

#include "analog_joystick.hpp"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

// left track transformation

void test_transform_to_left_track_F()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_left_track(32767, 0);

    TEST_ASSERT_EQUAL_INT16(32767, result);
}

void test_transform_to_left_track_R()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_left_track(-32768, 0);

    TEST_ASSERT_EQUAL_INT16(-32768, result);
}

void test_transform_to_left_track_half_F()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_left_track(16383, 0);

    TEST_ASSERT_EQUAL_INT16(16383, result);
}

void test_transform_to_left_track_half_R()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_left_track(-16384, 0);

    TEST_ASSERT_EQUAL_INT16(-16384, result);
}

void test_transform_to_left_track_FL()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_left_track(32767, -32768);

    TEST_ASSERT_EQUAL_INT16(32767, result);
}

void test_transform_to_left_track_RL()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_left_track(-32768, -32768);

    TEST_ASSERT_EQUAL_INT16(-32768, result);
}

void test_transform_to_left_track_FR()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_left_track(32767, 32767);

    TEST_ASSERT_EQUAL_INT16(0, result);
}

void test_transform_to_left_track_RR()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_left_track(-32768, 32767);

    TEST_ASSERT_EQUAL_INT16(0, result);
}

void test_transform_to_left_track_half_FR() // turn at 50% on right
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_left_track(32767, 16383);

    TEST_ASSERT_EQUAL_INT16(16383, result);
}

void test_transform_to_left_track_half_RR() // turn at 50% on right
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_left_track(-32768, 16383);

    TEST_ASSERT_EQUAL_INT16(-16384, result);
}

// right track transformation

void test_transform_to_right_track_F()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_right_track(32767, 0);

    TEST_ASSERT_EQUAL_INT16(32767, result);
}

void test_transform_to_right_track_R()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_right_track(-32768, 0);

    TEST_ASSERT_EQUAL_INT16(-32768, result);
}

void test_transform_to_right_track_half_F()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_right_track(16383, 0);

    TEST_ASSERT_EQUAL_INT16(16383, result);
}

void test_transform_to_right_track_half_R()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_right_track(-16384, 0);

    TEST_ASSERT_EQUAL_INT16(-16384, result);
}

void test_transform_to_right_track_FL()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_right_track(32767, -32768);

    TEST_ASSERT_EQUAL_INT16(0, result);
}

void test_transform_to_right_track_RL()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_right_track(-32768, -32768);

    TEST_ASSERT_EQUAL_INT16(0, result);
}

void test_transform_to_right_track_FR()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_right_track(32767, 32767);

    TEST_ASSERT_EQUAL_INT16(32767, result);
}

void test_transform_to_right_track_RR()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_right_track(-32768, 32767);

    TEST_ASSERT_EQUAL_INT16(-32768, result);
}

void test_transform_to_right_track_half_FL() // turn at 50% on right
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_right_track(32767, -16383);

    TEST_ASSERT_EQUAL_INT16(16384, result);
}

void test_transform_to_right_track_half_RL() // turn at 50% on right
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_to_right_track(-32768, -16383);

    TEST_ASSERT_EQUAL_INT16(-16385, result);
}

// transform ADC

void test_transform_ADC_0() 
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_ADC(0);

    TEST_ASSERT_EQUAL_INT16(-32768, result);
}

void test_transform_ADC_1023()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_ADC(1023);

    TEST_ASSERT_EQUAL_INT16(32767, result);
}

void test_transform_ADC_512()
{
    AnalogJoystick Joystick;
    int16_t result = Joystick.transform_ADC(512);

    TEST_ASSERT_EQUAL_INT16(0, result);
}

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!
    // left
    RUN_TEST(test_transform_to_left_track_F);
    RUN_TEST(test_transform_to_left_track_R);
    RUN_TEST(test_transform_to_left_track_half_F);
    RUN_TEST(test_transform_to_left_track_half_R);
    RUN_TEST(test_transform_to_left_track_FL);
    RUN_TEST(test_transform_to_left_track_RL);
    RUN_TEST(test_transform_to_left_track_FR);
    RUN_TEST(test_transform_to_left_track_RR);
    RUN_TEST(test_transform_to_left_track_half_FR);
    RUN_TEST(test_transform_to_left_track_half_RR);
    // right
    RUN_TEST(test_transform_to_right_track_F);
    RUN_TEST(test_transform_to_right_track_R);
    RUN_TEST(test_transform_to_right_track_half_F);
    RUN_TEST(test_transform_to_right_track_half_R);
    RUN_TEST(test_transform_to_right_track_FL);
    RUN_TEST(test_transform_to_right_track_RL);
    RUN_TEST(test_transform_to_right_track_FR);
    RUN_TEST(test_transform_to_right_track_RR);
    RUN_TEST(test_transform_to_right_track_half_FL);
    RUN_TEST(test_transform_to_right_track_half_RL);
    // transform ADC
    RUN_TEST(test_transform_ADC_0);
    RUN_TEST(test_transform_ADC_1023);
    RUN_TEST(test_transform_ADC_512);
}

void loop()
{
    UNITY_END(); // stop unit testing
}
