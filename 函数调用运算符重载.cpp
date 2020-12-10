//#include <iostream>
//#include <string>
//
//using namespace std;
//
//
//class MyPrint
//{
//public:
//	void operator()(string test)
//	{
//		cout << test << endl;
//	}
//};
//
//class MyAdd
//{
//public:
//	int operator()(int a, int b)
//	{
//		return a + b;
//	}
//};
//
//void test01()
//{
//	MyPrint myPrint;
//	// 被称为仿函数（重载之后）
//	myPrint("hello myPrint");
//}
//
//void test02()
//{
//	MyAdd myAdd;
//	int i = myAdd(10, 20);
//	cout << i << endl;
//
//	cout << MyAdd()(10, 20) << endl;
//}
//
//int main()
//{
//	test01();
//	test02();
//
//	return 0;
//}