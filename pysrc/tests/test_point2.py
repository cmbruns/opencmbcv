import unittest
import cmbcv

class TestPoint2(unittest.TestCase):
    def setUp(self):
        self.vec1 = cmbcv.point2_t(5,2)

    def testPoint2(self):
        v = self.vec1
        self.assertEqual(1+1, 2) # positive control
        self.assertEqual(v.x, 5)
        self.assertEqual(v.y, 2)

    def testNumberEquality(self):
        # sanity check to make sure we understand what "==" means
        self.assertEqual(5, 5)
        self.assertTrue(5 == 5)
        self.assertFalse(5 == 4)
        self.assertFalse(5 != 5)
        self.assertTrue(5 != 4)
                
    def testListEquality(self):
        # make sure "==" works with built in types the way we
        # expect, before testing the same way on our types, such as point2_t.
        # And "!=" too.
        self.assertEqual([1, 2], [1, 2])
        self.assertTrue([1, 2] == [1, 2])
        self.assertFalse([1, 2] == [1, 3])
        self.assertFalse([1, 2] != [1, 2])
        self.assertTrue([1, 2] != [1, 3])
        
    def testTupleEquality(self):
        # make sure "==" works with built in types the way we
        # expect, before testing the same way on our types, such as point2_t.
        # And "!=" too.
        self.assertEqual((1, 3), (1, 3))
        self.assertEqual(tuple([1, 3]), (1, 3))
        self.assertTrue((1, 3) == (1, 3))
        self.assertFalse((1, 3) == (1, 2))
        self.assertFalse((1, 3) != (1, 3))
        self.assertTrue((1, 3) != (1, 2))
        
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
        self.assertFalse(v == v3)
        self.assertFalse(v != v2)
        
    # It appears that tuples cannot be compared to lists with == nor !=

    def testListIndex(self):
        li = [1, 2]
        self.assertEqual(li[0], 1)
        self.assertEqual(li[1], 2)
        self.assertEqual(li[-1], 2)
        self.assertEqual(li[-2], 1)
        self.assertTrue(li[0] == 1)
        self.assertTrue(li[0] != 2)
        self.assertFalse(li[0] == 2)
        self.assertFalse(li[0] != 1)
        self.assertTrue(li[1] == 2)
        self.assertTrue(li[1] != 1)
        self.assertFalse(li[1] == 1)
        self.assertFalse(li[1] != 2)
        # Make sure that using index out of range causes an error
        self.assertRaises(IndexError, li.__getitem__, 2)
        # TODO - test slicing also
        
    def testTupleIndex(self):
        t = (1, 3)
        self.assertEqual(t[0], 1)
        self.assertEqual(t[1], 3)
        self.assertEqual(t[-1], 3)
        self.assertEqual(t[-2], 1)
        self.assertTrue(t[0] == 1)
        self.assertTrue(t[0] != 3)
        self.assertFalse(t[0] == 3)
        self.assertFalse(t[0] != 1)
        self.assertTrue(t[1] == 3)
        self.assertTrue(t[1] != 1)
        self.assertFalse(t[1] == 1)
        self.assertFalse(t[1] != 3)
        
    def testPoint2Index(self):
        v = self.vec1
        self.assertEqual(v[0], 5)
        self.assertEqual(v[1], 2)
        self.assertEqual(v[-1], 2)
        self.assertEqual(v[-2], 5)
        self.assertTrue(v[0] == 5)
        self.assertTrue(v[0] != 2)
        self.assertFalse(v[0] == 2)
        self.assertFalse(v[0] != 5)
        self.assertTrue(v[1] == 2)
        self.assertTrue(v[1] != 5)
        self.assertFalse(v[1] == 5)
        self.assertFalse(v[1] != 2)
        
if __name__ == '__main__':
    unittest.main()

