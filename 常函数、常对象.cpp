//#include <iostream>
//#include <string>
//
//
//using namespace std;
//
///*
//this 指针是一个指针常量，指向无法改变
//*/
//struct Person
//{
//	void ShowPerson() const
//	{
//		//m_age = 100; // 报错，常函数中不能修改普通变量的值
//		m_height = 170; // mutable 关键字修饰的变量可以修改
//	}
//
//	void Func() {}
//
//	int m_age = 18;
//	mutable int m_height = 160;
//};
//
//void test01()
//{
//	int a = 10;
//	const int* p = NULL;
//	p = &a;
//	cout << *p << endl;
//
//	int* const p_ = NULL;
//	//p_ = &a; // 不可以修改指针指向
//	//cout << *p_ << endl;
//}
//
//void test02()
//{
//	Person p;
//	cout << p.m_height << endl;
//	p.ShowPerson();
//	cout << p.m_height << endl;
//}
//
//void test03()
//{
//	const Person p;
//	//p.m_age = 10; // 不可以修改常对象的成员变量
//	//p.Func(); // 常对象不允许调用普通成员函数，因为普通成员函数可以修改对象的成员变量，而常对象不允许修改，因此相违背了
//	p.ShowPerson(); // 只能调用常函数
//}
//
//int main()
//{
//	test02();
//
//	return 0;
//}
//
