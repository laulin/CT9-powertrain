import time
import machine

from joystick import Joystick
from motor_controler import MotorControler
from servo import Servo
from optical_encoder import OpticalEncoder
from lp_filter import *

#LED
LED_PIN = 2

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

# Left encoder
LEFT_ENCODER_A = 26
LEFT_ENCODER_B = 25

# Right encoder
RIGHT_ENCODER_A = 15
RIGHT_ENCODER_B = 0

# Define the max rotation per seconde
ENCODER_ROUND_STEPS = 1024
ENCODER_GEAR_RATION = 2
TIME_STEP = 100
#MAX_ANGULAR_SPEED = int(TIME_STEP * ENCODER_ROUND_STEPS * ENCODER_GEAR_RATION / 1000)
MAX_ANGULAR_SPEED = 50

# PID
PWM_MAX = 1023
P_FACTOR = 5
I_FACTOR = 0
D_FACTOR = 0

class Powertrain:
    def __init__(self, p_factor:float=P_FACTOR, i_factor:float=I_FACTOR, d_factor:float=D_FACTOR) -> None:
        self._joystick = Joystick(FORWARD_PIN, REVERSE_PIN, LEFT_PIN, RIGHT_PIN)

        self._left_motor_controler = MotorControler(LEFT_MOTOR_PWM, LEFT_MOTOR_A, LEFT_MOTOR_B)
        self._right_motor_controler = MotorControler(RIGHT_MOTOR_PWM, RIGHT_MOTOR_A, RIGHT_MOTOR_B)

        self._left_encoder = OpticalEncoder(LEFT_ENCODER_A, LEFT_ENCODER_B)
        self._right_encoder = OpticalEncoder(RIGHT_ENCODER_A, RIGHT_ENCODER_B)

        self._left_servo = Servo(p_factor, i_factor, d_factor)
        self._right_servo = Servo(p_factor, i_factor, d_factor)

        self._left_lp_filter = LPFilter(gauss_factors(5, 0.1))
        self._right_lp_filter = LPFilter(gauss_factors(5, 0.1))

        self._led = machine.Pin(LED_PIN, machine.Pin.OUT)
        self._led.off()

    def loop(self):
        while True:
            self._led.on()
            left_consign, right_consign = self._joystick.get(MAX_ANGULAR_SPEED)

            left_feedback = self._left_encoder.get_and_clear_counter()
            left_pwm = self._left_servo.update(left_consign, left_feedback, TIME_STEP)
            filtered_left_pwm = self._left_lp_filter.filter(left_pwm)
            self._left_motor_controler.set(filtered_left_pwm)

            right_feedback = -self._right_encoder.get_and_clear_counter()
            right_pwm = self._left_servo.update(right_consign, right_feedback, TIME_STEP)
            filtered_right_pwm = self._right_lp_filter.filter(right_pwm)
            self._right_motor_controler.set(filtered_right_pwm)

            print(f"[{left_consign},{left_feedback},{left_pwm},{filtered_left_pwm}],[{right_consign},{right_feedback},{right_pwm},{filtered_right_pwm}]")
            self._led.off()
            time.sleep_ms(TIME_STEP)
