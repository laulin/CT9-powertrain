import time

from joystick import Joystick
from ramp import Ramp
from motor_controler import MotorControler
from servo import Servo
from optical_encoder import OpticalEncoder

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
MAX_ANGULAR_SPEED = int(ENCODER_ROUND_STEPS * ENCODER_GEAR_RATION / TIME_STEP)

# PID
PWM_MAX = 1024
P_FACTOR = PWM_MAX/MAX_ANGULAR_SPEED
I_FACTOR = 0
D_FACTOR = 0

class Powertrain:
    def __init__(self) -> None:
        self._joystick = Joystick(FORWARD_PIN, REVERSE_PIN, LEFT_PIN, RIGHT_PIN)

        self._left_ramp = Ramp(RAMP_SIZE, RAMP_BREAK_FACTOR)
        self._right_ramp = Ramp(RAMP_SIZE, RAMP_BREAK_FACTOR)

        self._left_motor_controler = MotorControler(LEFT_MOTOR_PWM, LEFT_MOTOR_A, LEFT_MOTOR_B)
        self._right_motor_controler = MotorControler(RIGHT_MOTOR_PWM, RIGHT_MOTOR_A, RIGHT_MOTOR_B)

        self._left_encoder = OpticalEncoder(LEFT_ENCODER_A, LEFT_ENCODER_B)
        self._right_encoder = OpticalEncoder(RIGHT_ENCODER_A, RIGHT_ENCODER_B)

        self._left_servo = Servo(P_FACTOR, I_FACTOR, D_FACTOR, PWM_MAX)
        self._right_servo = Servo(P_FACTOR, I_FACTOR, D_FACTOR, PWM_MAX)

    def loop(self):
        while True:
            try:
                left_direction, right_direction = self._joystick.get()
                
                self._left_ramp.update(left_direction, TIME_STEP)
                self._right_ramp.update(right_direction, TIME_STEP)

                left_consign = self._left_ramp.get_normalized(MAX_ANGULAR_SPEED)
                left_feedback = 
                #left_pwm = self._left_servo.update(left_consign, left_feedback)
                left_pwm = self._left_servo.update(left_consign, 0)
                self._left_motor_controler.set(left_pwm)

                right_consign = self._right_ramp.get_normalized(MAX_ANGULAR_SPEED)
                right_feedback = 0
                #right_pwm = self._left_servo.update(right_consign, right_feedback)
                right_pwm = self._left_servo.update(right_consign, 0)
                self._right_motor_controler.set(right_pwm)

                print(f"[{left_direction},{right_direction}],[{left_consign},{left_feedback},{left_pwm}],[{right_consign},{right_feedback},{right_pwm}]")
                time.sleep_ms(TIME_STEP)

            except Exception as e:
                print(e)
