from joystick import Joystick
from ramp import Ramp
from motor_controler import MotorControler
import time

# Joystick
FORWARD_PIN = 21
REVERSE_PIN = 19
LEFT_PIN = 22
RIGHT_PIN = 23

# RAMP
RAMP_SIZE = 2000
RAMP_BREAK_FACTOR = 2

# Left motor
LEFT_MOTOR_A = 27
LEFT_MOTOR_B = 14
LEFT_MOTOR_PWM = 12

# Right motor
RIGHT_MOTOR_A = 17
RIGHT_MOTOR_B = 16
RIGHT_MOTOR_PWM = 4

class Powertrain:
    def __init__(self) -> None:
        self._joystick = Joystick(FORWARD_PIN, REVERSE_PIN, LEFT_PIN, RIGHT_PIN)

        self._left_ramp = Ramp(RAMP_SIZE, RAMP_BREAK_FACTOR)
        self._right_ramp = Ramp(RAMP_SIZE, RAMP_BREAK_FACTOR)

        self._left_motor_controler = MotorControler(LEFT_MOTOR_PWM, LEFT_MOTOR_A, LEFT_MOTOR_B)
        self._right_motor_controler = MotorControler(RIGHT_MOTOR_PWM, RIGHT_MOTOR_A, RIGHT_MOTOR_B)

    def loop(self):
        start_time = time.ticks_ms()
        while True:
            try:
                # delta = time.ticks_diff(time.ticks_ms(), start_time)
                # print("delta", delta)
                delta = 10
                left_direction, right_direction = self._joystick.get()
                print("direction", left_direction, right_direction)

                self._left_ramp.update(left_direction, delta)
                self._right_ramp.update(right_direction, delta)

                left_consign = self._left_ramp.get_normalized()
                self._left_motor_controler.set(left_consign)

                right_consign = self._right_ramp.get_normalized()
                self._right_motor_controler.set(right_consign)

                print("")
                time.sleep_ms(10)

            except Exception as e:
                print(e)


            start_time = time.ticks_ms()