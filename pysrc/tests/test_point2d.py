import unittest
import cmbcv

class TestPoint2d(unittest.TestCase):

    def setUp(self):
        self.vec1 = cmbcv.point2d_t(1,2)

    def testPoint2d(self):
        self.assertEqual(1+1, 2)

if __name__ == '__main__':
    unittest.main()

