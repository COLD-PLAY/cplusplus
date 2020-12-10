//#include <iostream>
//
//using namespace std;
//
//class Integer
//{
//	friend ostream& operator<<(ostream& cout, Integer i);
//public:
//	Integer()
//	{
//		m_num = 0;
//	}
//
//	Integer(int n)
//	{
//		m_num = n;
//	}
//
//	// Ç°++
//	Integer& operator++()
//	{
//		m_num++;
//		return *this;
//	}
//
//	// ºó++
//	Integer operator++(int)
//	{
//		Integer tmp = *this;
//		m_num++;
//		return tmp;
//	}
//
//	Integer& operator=(Integer& i)
//	{
//		m_num = i.m_num+1;
//		return *this;
//	}
//
//	bool operator<(Integer& i)
//	{
//		return m_num < i.m_num;
//	}
//
//	bool operator>(Integer& i)
//	{
//		return m_num > i.m_num;
//	}
//
//	bool operator==(Integer& i)
//	{
//		return m_num == i.m_num;
//	}
//
//private:
//	int m_num;
//};
//
//ostream& operator<<(ostream& cout, Integer i)
//{
//	cout << i.m_num;
//	return cout;
//}
//
//int main()
//{
//	Integer i(10);
//	Integer i1, i2;
//	i2 = i1 = i;
//
//	cout << i2 << ' ' << i1 << endl;
//	cout << (i1 == i2) << endl;
//
//	return 0;
//}