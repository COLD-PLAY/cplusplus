//#include <iostream>
//#include <string>
//
//
//using namespace std;
//
////void goodGay(Building* building)
////{
////	cout << "�û���ȫ�ֺ��� ���ڷ���: " << building->m_sittingRoom << endl;
////	cout << "�û���ȫ�ֺ��� ���ڷ���: " << building->m_redRoom << endl;
////}
//
//struct Building
//{
//	// goodGay ȫ�ֺ�����һ����Ԫ���������Է���˽�г�Ա
//	//friend void goodGay(Building* building);
//	// GoodGay ����һ����Ԫ�࣬���Է���˽�г�Ա
//	friend struct GoodGay;
//	string m_sittingRoom;
//	Building()
//	{
//		m_sittingRoom = "����";
//		m_redRoom = "����";
//	}
//private:
//	string m_redRoom;
//};
//
//struct GoodGay
//{
//	Building* m_building;
//	GoodGay()
//	{
//		m_building = new Building;
//	}
//	void visit()
//	{
//		cout << "�û����� ���ڷ���: " << m_building->m_sittingRoom << endl;
//		cout << "�û����� ���ڷ���: " << m_building->m_redRoom << endl;
//	}
//};
//
////void test01()
////{
////	Building building;
////	goodGay(&building);
////}
//
//void test02()
//{
//	GoodGay goodGay;
//	goodGay.visit();
//}
//
//int main()
//{
//	test02();
//	
//	return 0;
//}
//
