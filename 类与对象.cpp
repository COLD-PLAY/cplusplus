//#include <iostream>
//
//using namespace std;
//
//struct Person
//{
//	int m_age; // �Ǿ�̬��Ա���� ������Ķ�����
//	static int m_height; // ��̬��Ա���� ��������Ķ�����
//
//	void f() {} // �Ǿ�̬��Ա���� ��������Ķ����ϣ�һ�ݣ���Ϊ���ú�����ʱ����һ��this ָ�룬Python -> self��
//	static void f_() {} // ��̬��Ա���� ��������Ķ����ϣ�һ�ݣ�
//	
//	Person() {}
//	Person(const Person& p)
//	{
//		cout << "�������캯��" << endl;
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
//	// ��ʽ���˼�룬����һֱ����׷��
//	p.Add(10).Add(10).Add(10);
//	cout << p.m_age << endl;
//
//	return 0;
//}
//
// 