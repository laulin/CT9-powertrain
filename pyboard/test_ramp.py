import unittest
from unittest import result
from unittest.case import expectedFailure

from ramp import Ramp

class TestRamp(unittest.TestCase):
    def setUp(self) -> None:
        self.r = Ramp(10)

    def test_forward_1(self):
        self.r.update(1,1)
        result = self.r.get()
        expected = 1
        self.assertEqual(result, expected)

    def test_forward_2(self):
        self.r.update(1,1)
        self.r.update(1,10)
        result = self.r.get()
        expected = 10
        self.assertEqual(result, expected)

    def test_forward_release_1(self):
        self.r.update(1,5)
        self.r.update(0,3)
        result = self.r.get()
        expected = 2
        self.assertEqual(result, expected)

    def test_forward_release_2(self):
        self.r.update(1,5)
        self.r.update(0,6)
        result = self.r.get()
        expected = 0
        self.assertEqual(result, expected)

    def test_forward_brake_1(self):
        self.r.update(1,7)
        self.r.update(-1,3)
        result = self.r.get()
        expected = 1
        self.assertEqual(result, expected)

    def test_forward_brake_2(self):
        self.r.update(1,5)
        self.r.update(-1,6)
        result = self.r.get()
        expected = -7
        self.assertEqual(result, expected)

    def test_reverse_1(self):
        self.r.update(-1,1)
        result = self.r.get()
        expected = -1
        self.assertEqual(result, expected)

    def test_reverse_2(self):
        self.r.update(-11,1)
        self.r.update(-1,10)
        result = self.r.get()
        expected = -10
        self.assertEqual(result, expected)

    def test_reverse_release_1(self):
        self.r.update(-1,5)
        self.r.update(0,3)
        result = self.r.get()
        expected = -2
        self.assertEqual(result, expected)

    def test_reverse_release_2(self):
        self.r.update(-1,5)
        self.r.update(0,6)
        result = self.r.get()
        expected = 0
        self.assertEqual(result, expected)

    def test_reverse_brake_1(self):
        self.r.update(-1,7)
        self.r.update(1,3)
        result = self.r.get()
        expected = -1
        self.assertEqual(result, expected)

    def test_reverse_brake_2(self):
        self.r.update(-1,5)
        self.r.update(1,6)
        result = self.r.get()
        expected = 7
        self.assertEqual(result, expected)

if __name__ == "__main__":
    unittest.main()