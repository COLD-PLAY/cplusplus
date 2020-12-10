//#include "Point.hpp"
//
//using namespace std;
//
//template <class T>
//T sum(T* begin, T* end) {
//	T sum(0);
//	for (T *p = begin; p != end; p++) {
//		sum = sum + *p;
//	}
//	return sum;
//}
//
//ostream& operator <<(ostream& out, const Point& a) {
//	out << "(" << a.x << "," << a.y << ")";
//	return out;
//}
//
//int main() {
//	int iarr[3] = { 1, 2, 3 };
//	double darr[3] = { .5, .3, .8 };
//	Point parr[3] = { {0, 1}, {1, 2}, {2, 3} };
//	cout << "sum of iarr: " << sum<int>(iarr, iarr + 3) << endl;
//	cout << "sum of darr: " << sum<double>(darr, darr + 3) << endl;
//	cout << "sum of parr: " << sum<Point>(parr, parr + 3) << endl;
//	return 0;
//}