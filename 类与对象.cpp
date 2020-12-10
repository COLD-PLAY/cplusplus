//#include <iostream>
//
//using namespace std;
//
//struct Person
//{
//	int m_age; // 非静态成员变量 属于类的对象上
//	static int m_height; // 静态成员变量 不属于类的对象上
//
//	void f() {} // 非静态成员函数 不属于类的对象上（一份，因为调用函数的时候会给一个this 指针，Python -> self）
//	static void f_() {} // 静态成员函数 不属于类的对象上（一份）
//	
//	Person() {}
//	Person(const Person& p)
//	{
//		cout << "拷贝构造函数" << endl;
//	}
//
//	Person& Add(int age)
//	{
//		m_age += age;
//		return *this;
//	}
//};
//
////int Person::m_height = 170;
//
//int main()
//{
//	Person p;
//	cout << sizeof(p) << endl;
//
//	p.m_age = 18;
//
//	// 链式编程思想，可以一直往后追加
//	p.Add(10).Add(10).Add(10);
//	cout << p.m_age << endl;
//
//	return 0;
//}
//
// 