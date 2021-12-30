import machine
import pyb

class OpticalEncoder:
    # Hardware driver for optical encoder. Used to give the angular position of the sprocket.
    # Take care of teh gear ratio induced by the pullet.
    def __init__(self, pin_a:int, pin_b:int) -> None:
        self._pin_a = machine.Pin(pin_a, machine.Pin.IN, machine.Pin.PULL_UP)
        self._pin_b = machine.Pin(pin_b, machine.Pin.IN, machine.Pin.PULL_UP)

        self._counter = 0

        self._pin_a.irq(handler=self.irq, trigger=Pin.IRQ_RISING, hard=True)


    def irq(self, pin):
        if self._pin_b.value():
            self._counter += 1
        else:
            self._counter -= 1

    def get_and_clear_counter(self):
        irq_state = pyb.disable_irq()
        output = self._counter
        self._counter = 0
        pyb.enable_irq(irq_state)

        return output

    