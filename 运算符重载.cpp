//#include <iostream>
//
//using namespace std;
//
//
//class Person
//{
//	friend ostream& operator<<(ostream& cout, Person& p);
//	friend Person operator+(Person& p1, Person& p2);
//	friend Person operator+(Person& p, string name);
//public:
//	Person() : m_name("liaozhou") {}
//	//Person(const Person& p) { cout << "拷贝构造函数" << endl; }
//
//	//Person operator+(Person& p)
//	//{
//	//	Person tmp;
//	//	tmp.m_name = m_name + p.m_name;
//	//	return tmp;
//	//}
//
//	//Person operator+(string name)
//	//{
//	//	Person tmp;
//	//	tmp.m_name = m_name + name;
//	//	return tmp;
//	//}
//
//private:
//	string m_name;
//};
//
//Person operator+(Person& p1, Person& p2)
//{
//	Person tmp;
//	tmp.m_name = p1.m_name + p2.m_name;
//	return tmp;
//}
//
//Person operator+(Person& p, string name)
//{
//	Person tmp;
//	tmp.m_name = p.m_name + name;
//	return tmp;
//}
//
//ostream& operator<<(ostream& cout, Person& p)
//{
//	cout << p.m_name;
//	return cout;
//}
//
//int main()
//{
//	Person p1;
//	Person p2;
//	// 成员函数运算符重载，两种调用方式都可以
//	//Person p3 = p1.operator+(p2);
//	//Person p3 = p1 + p2;
//	//cout << p3 << endl;
//
//	// 全局函数运算符重载
//	//Person p3 = operator+(p1, p2);
//	//Person p3 = p1 + p2;
//	//cout << p3 << endl;
//
//	Person p4 = operator+(p1, "shishuaibi");
//	cout << p4 << endl;
//	
//	return 0;
//}
//
