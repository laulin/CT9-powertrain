try:
    import machine
except:
    print("Bypass machine import")


def transform(forward:bool, reverse:bool, left:bool, right:bool):
    if left and right:
        raise Exception("Left and right conflict")

    if forward and reverse:
        raise Exception("forward and reverse conflict")

    if forward:
        if not right and not left:
            return 1, 1
        elif left:
            return 0,1
        elif right:
            return 1,0 
    elif reverse:
        if not right and not left:
            return -1, -1
        elif left:
            return 0,-1
        elif right:
            return -1,0 
    else:
        return 0,0

class Joystick:
    def __init__(self, forward_pin, reverse_pin, left_pin, right_pin):
        self._forward_pin = machine.Pin(forward_pin, machine.Pin.IN, machine.Pin.PULL_UP)
        self._reverse_pin = machine.Pin(reverse_pin, machine.Pin.IN, machine.Pin.PULL_UP)
        self._left_pin = machine.Pin(left_pin, machine.Pin.IN, machine.Pin.PULL_UP)
        self._right_pin = machine.Pin(right_pin, machine.Pin.IN, machine.Pin.PULL_UP)

    def get(self):
        forward = not self._forward_pin.value()
        reverse = not self._reverse_pin.value()
        left = not self._left_pin.value()
        right = not self._right_pin.value()
        #print("inputs : ", forward, reverse, left, right)
        return transform(forward, reverse, left, right)