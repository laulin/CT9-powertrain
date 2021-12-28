class Ramp:
    def __init__(self, max_count:int) -> None:
        self._max_count = max_count
        self._count = 0

    def update(self, direction:int, inc:int):
        if direction > 0:
            if self._count >= 0:
                self._count = self._count + inc
            else:
                self._count = self._count + inc*2

        elif direction < 0:
            if self._count <= 0:
                self._count = self._count - inc
            else:
                self._count = self._count - inc*2

        else: # == 0
            if self._count > 0:
                self._count = max(0, self._count - inc)
            elif self._count < 0:
                self._count = min(0, self._count + inc)
            else:
                self._count = 0

        self._count = max(-self._max_count, self._count)
        self._count = min(self._max_count, self._count)

    def get(self):
        return self._count
