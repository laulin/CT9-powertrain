#include <Arduino.h>
#include <unity.h>

#include "timer.hpp"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_get_delta(void)
{
    Timer timer;
    timer.begin();
    delay(100);
    unsigned long delta = timer.get_delta();
    TEST_ASSERT_TRUE(delta >= 100);
}

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!
    RUN_TEST(test_get_delta);
}

void loop()
{
    UNITY_END(); // stop unit testing
}
