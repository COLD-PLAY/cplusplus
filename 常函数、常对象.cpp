//#include <iostream>
//#include <string>
//
//
//using namespace std;
//
///*
//this ָ����һ��ָ�볣����ָ���޷��ı�
//*/
//struct Person
//{
//	void ShowPerson() const
//	{
//		//m_age = 100; // �����������в����޸���ͨ������ֵ
//		m_height = 170; // mutable �ؼ������εı��������޸�
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
//	//p_ = &a; // �������޸�ָ��ָ��
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
//	//p.m_age = 10; // �������޸ĳ�����ĳ�Ա����
//	//p.Func(); // ���������������ͨ��Ա��������Ϊ��ͨ��Ա���������޸Ķ���ĳ�Ա�������������������޸ģ������Υ����
//	p.ShowPerson(); // ֻ�ܵ��ó�����
//}
//
//int main()
//{
//	test02();
//
//	return 0;
//}
//
