import unittest
from unittest import result
from unittest.case import expectedFailure
from joystick import transform

class TestJoystick(unittest.TestCase):
    def test_forward(self):
        result = transform(1, 0, 0, 0)
        expected = (1,1)
        self.assertEqual(result, expected)

    def test_forward_left(self):
        result = transform(1, 0, 1, 0)
        expected = (0,1)
        self.assertEqual(result, expected)

    def test_forward_right(self):
        result = transform(1, 0, 0, 1)
        expected = (1,0)
        self.assertEqual(result, expected)

    def test_reverse(self):
        result = transform(0, 1, 0, 0)
        expected = (-1,-1)
        self.assertEqual(result, expected)

    def test_reverse_left(self):
        result = transform(0, 1, 1, 0)
        expected = (0,-1)
        self.assertEqual(result, expected)

    def test_reverse_right(self):
        result = transform(0, 1, 0, 1)
        expected = (-1,0)
        self.assertEqual(result, expected)

    def test_left(self):
        result = transform(0, 0, 1, 0)
        expected = (0,0)
        self.assertEqual(result, expected)

    def test_right(self):
        result = transform(0, 0, 0, 1)
        expected = (0,0)
        self.assertEqual(result, expected)

    def test_idle(self):
        result = transform(0, 0, 0, 0)
        expected = (0,0)
        self.assertEqual(result, expected)


if __name__ == "__main__":
    unittest.main()