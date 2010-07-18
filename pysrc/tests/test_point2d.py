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
        # self.assertEqual(5, 4)
        self.assertTrue(5 == 5)
        # self.assertTrue(5 == 4)
        self.assertFalse(5 == 4)
        # self.assertFalse(5 == 5)
        self.assertFalse(5 != 5)
        # self.assertFalse(5 != 4)
        self.assertTrue(5 != 4)
        # self.assertTrue(5 != 5)
        
    def testListEquality(self):
        self.assertEqual([1, 2], [1, 2])
        #self.assertEqual([1, 2], [1, 1])
        
    def testTupleEquality(self):
        self.assertEqual((1, 3), (1, 3))
        self.assertEqual(tuple([1, 3]), (1, 3))
        
    def testPoint2dEquality(self):
        v = self.vec1
        self.assertEqual(v, v)
        v2 = cmbcv.point2d_t(5,2)
        self.assertEqual(v.x, v2.x)
        self.assertEqual(v.y, v2.y)
        self.assertTrue(v == v2)
        self.assertEqual(v, v2)
    
    # It appears that tuples cannot be compared to lists with == nor !=
        
        
if __name__ == '__main__':
    unittest.main()

