//#include <iostream>
//#include <string>
//
//
//using namespace std;
//
////void goodGay(Building* building)
////{
////	cout << "好基友全局函数 正在访问: " << building->m_sittingRoom << endl;
////	cout << "好基友全局函数 正在访问: " << building->m_redRoom << endl;
////}
//
//struct Building
//{
//	// goodGay 全局函数是一个友元函数，可以访问私有成员
//	//friend void goodGay(Building* building);
//	// GoodGay 类是一个友元类，可以访问私有成员
//	friend struct GoodGay;
//	string m_sittingRoom;
//	Building()
//	{
//		m_sittingRoom = "客厅";
//		m_redRoom = "卧室";
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
//		cout << "好基友类 正在访问: " << m_building->m_sittingRoom << endl;
//		cout << "好基友类 正在访问: " << m_building->m_redRoom << endl;
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
