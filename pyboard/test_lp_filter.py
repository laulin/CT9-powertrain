import unittest

from lp_filter import LPFilter
from lp_filter import gauss_factors

class TestLPFilter(unittest.TestCase):
    def test_1(self):
        lp = LPFilter([1,1,1,1])
        result= lp.filter(4)
        expected = 1

        self.assertEqual(result, expected)

    def test_2(self):
        lp = LPFilter([1,1,1,1])
        result= lp.filter(2) # should be ejected
        result= lp.filter(4)
        result= lp.filter(4)
        result= lp.filter(4)
        result= lp.filter(0)
        expected = 3

        self.assertEqual(result, expected)

    def test_3(self):
        factors = gauss_factors(10, 0.05)
        print(factors)


if __name__ == "__main__":
    unittest.main()