import unittest
import cmbcv

class TestPoint2(unittest.TestCase):
    def setUp(self):
        self.vec1 = cmbcv.point2_t(5,2)

    def testPoint2(self):
        v = self.vec1
        self.assertEqual(1+1, 2)
        self.assertEqual(v.x, 5)
        self.assertEqual(v.y, 2)

    def testNumberEquality(self):
        self.assertEqual(5, 5)
        self.assertTrue(5 == 5)
        self.assertFalse(5 == 4)
        self.assertFalse(5 != 5)
        self.assertTrue(5 != 4)
                
    def testListEquality(self):
        self.assertEqual([1, 2], [1, 2])
        
    def testTupleEquality(self):
        self.assertEqual((1, 3), (1, 3))
        self.assertEqual(tuple([1, 3]), (1, 3))
        
    def testPoint2Equality(self):
        v = self.vec1
        self.assertEqual(v, v)
        v2 = cmbcv.point2_t(5,2)
        v3 = cmbcv.point2_t(4,1)
        self.assertEqual(v.x, v2.x)
        self.assertEqual(v.y, v2.y)
        self.assertEqual(v, v2)
        self.assertTrue(v == v2)
        self.assertTrue(v != v3)
        
    # It appears that tuples cannot be compared to lists with == nor !=
        
        
if __name__ == '__main__':
    unittest.main()

