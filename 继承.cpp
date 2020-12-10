//#include <iostream>
//#include <string>
//
//using namespace std;
//
//class Person
//{
//public:
//	//static int m_age;
//	int m_a;
//	int m_b;
//
//	Person()
//	{
//		cout << "Person::Person()" << endl;
//		m_both = 100;
//	}
//	~Person()
//	{
//		cout << "Person::~Person()" << endl;
//	}
//
//	void func()
//	{
//		cout << "Person::func()" << endl;
//	}
//
//	void func(int a)
//	{
//		cout << "Person::func(int a)" << endl;
//	}
//
//	int m_both;
//
//	static int m_static;
//
//private:
//	int m_c;
//};
//
//int Person::m_static = 100;
//
//class Man :public Person
//{
//public:
//	int m_d;
//
//	Man()
//	{
//		cout << "Man::Man()" << endl;
//		m_both = 200;
//	}
//	~Man()
//	{
//		cout << "Man::~Man()" << endl;
//	}
//
//	virtual void func()
//	{
//		cout << "Man::func()" << endl;
//	}
//
//	int m_both;
//
//	static int m_static;
//};
//
//int Man::m_static = 200;
//
//
//class Animal
//{
//public:
//	string name = "";
//};
//
//class Sheep :virtual public Animal
//{
//public:
//	Sheep()
//	{
//		name = "Sheep";
//	}
//};
//
//class Camal :virtual public Animal
//{
//public:
//	Camal()
//	{
//		name = "Camal";
//	}
//};
//
//class Alpaca :virtual public Sheep, virtual public Camal
//{
//public:
//	Alpaca()
//	{
//		cout << "name " << Sheep::name;
//	}
//};
//
//void test01()
//{
//	// 16
//	cout << sizeof(Man) << endl;
//}
//
//void test02()
//{
//	Man man;
//}
//
//void test03()
//{
//	Man man;
//	cout << "Man::m_both " << man.m_both << endl;
//	cout << "Man::Person::m_both " << man.Person::m_both << endl;
//}
//
//void test04()
//{
//	Man man;
//	man.func();
//	man.Person::func();
//	man.Person::func(2333);
//}
//
//void test05()
//{
//	Man man;
//	cout << "Man::m_static " << man.m_static << endl;
//	cout << "Person::m_static " << man.Person::m_static << endl;
//	
//	cout << "Man::m_static " << Man::m_static << endl;
//	cout << "Person::m_static " << Person::m_static << endl;
//
//	cout << "Person::m_static " << Man::Person::m_static << endl;
//}
//
//void test06()
//{
//	Alpaca alpaca;
//}
//
//int main()
//{
//	//test01();
//	//test02();
//	//test03();
//	//test04();
//	//test05();
//	test06();
//
//	return 0;
//}
