import unittest
import cmbcv

class TestPoint2d(unittest.TestCase):
    def setUp(self):
        self.vec1 = cmbcv.point2d_t(5,2)

    def testPoint2d(self):
        v = self.vec1
        self.assertEqual(1+1, 2)
        self.assertEqual(v.x, 5)
        self.assertEqual(v.y, 2)

    def testNumberEquality(self):
        self.assertEqual(5, 5)
        #self.assertEqual(5, 4)
        self.assertTrue(5 == 5)
        #self.assertTrue(5 == 4)
        self.assertFalse(5 == 4)
        #self.assertFalse(5 == 5)
        self.assertFalse(5 != 5)
        #self.assertFalse(5 != 4)
        self.assertTrue(5 != 4)
        #self.assertTrue(5 != 5)
        self.assertEqual([1, 2], [1, 2])
        #self.assertEqual([1, 2], [1, 1])

if __name__ == '__main__':
    unittest.main()

