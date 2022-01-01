import math

def gauss_factors(number, sigma):
    return [math.exp(-i**2 * sigma) for i in range(number)]

class LPFilter:
    # Low pass filter to smooth motor control
    def __init__(self, factors:list) -> None:
        self._factors = tuple(factors)
        self._norm = sum(factors)
        self._values = [0] * len(factors)

    def filter(self, value:int)->int:
        self._values = [value] + self._values[0:-1]

        # sum
        s = 0
        for i, f in enumerate(self._factors):
            s += f * self._values[i]

        # normalize
        output = int(s/self._norm)

        return output