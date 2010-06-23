#include "geom2D.hpp"
#include <iostream>

using namespace std;
using namespace cmbcv;

void testPoint2D() {
    Point2D x(1.0, 2.0);
    assert(x[0] == 1.0);
}

int main() {
    try {
        testPoint2D();
        cout << "passed" << endl;
        return 0;
    } 
    catch (std::exception exc) {
        cout << exc.what() << endl;
    }
    catch (...) {}
    cout << "!!! FAILED !!!" << endl;
    return 1;
}

