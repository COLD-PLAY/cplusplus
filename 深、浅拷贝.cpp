//#include <iostream>
//
//using namespace std;
///*
//深、浅拷贝：
//浅拷贝会将堆区数据的地址（指针）直接复制到新对象中（析构如果释放堆区内存时会造成重复释放）；
//深拷贝则会重新在堆区创建一块内存用于存放新对象中的堆区数据。
//*/
//struct Person
//{
//	int m_age;
//	int* m_height;
//	//Person() {}
//	//Person(const Person& p) : m_age(p.m_age), m_height(new int(*p.m_height)) {}
//	//~Person()
//	//{
//	//	if (m_height != NULL)
//	//		delete m_height;
//	//	m_height = NULL;
//	//}
//};
//
//int main()
//{
//	Person p;
//	p.m_age = 10;
//	p.m_height = new int(160);
//
//	Person p1(p);
//
//	cout << p.m_age << endl;
//	cout << p1.m_age << endl;
//
//	cout << p.m_height << endl;
//	cout << p1.m_height << endl;
//
//	system("pause");
//	return 0;
//}
//
