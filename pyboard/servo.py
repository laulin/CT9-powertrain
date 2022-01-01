class Servo:
    def __init__(self, p_factor:float, i_factor:float, d_factor:float, output_range:int=1023) -> None:
        # output range is absolute value
        # consign and feedback are signed
        self._p_factor = p_factor
        self._i_factor = i_factor
        self._d_factor = d_factor

        self._output_range = output_range

        self._n_1_value = 0
        self._sum = 0

    def update(self, consign:int, feedback:int, deltat:int):
        diff = consign - feedback

        # proportional
        output = self._p_factor * diff

        # derive
        derive = (diff - self._n_1_value) / deltat
        self._n_1_value = diff

        output += self._d_factor * derive

        # integral
        self._sum += diff * deltat
        output += self._i_factor * self._sum


        output = int(output)
        # clamp output
        output = min(output, self._output_range)
        output = max(output, - self._output_range)

        return output
        