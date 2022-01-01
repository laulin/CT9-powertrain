import machine

class MotorControler:
    def __init__(self, pwm_pin, a_pin, b_pin) -> None:
        self._pwm_pin = machine.Pin(pwm_pin)
        self._pwm = machine.PWM(self._pwm_pin)
        self._pwm.duty(0)

        self._a_pin = machine.Pin(a_pin, machine.Pin.OUT)
        self._a_pin.off()

        self._b_pin = machine.Pin(b_pin, machine.Pin.OUT)
        self._b_pin.off()

    def set(self, value):
        #print("set consign : ", value)
        if value > 0:
            self._a_pin.on()
            self._b_pin.off()
            self._pwm.duty(min(1023, value))
        elif value < 0:
            self._a_pin.off()
            self._b_pin.on()
            self._pwm.duty(max(-1023, -value))
        else:
            self._a_pin.off()
            self._b_pin.off()
            self._pwm.duty(0)