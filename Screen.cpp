//#include <iostream>
//
//using namespace std;
//
//class Screen
//{
//public:
//	typedef std::string::size_type pos;
//	Screen() = default;
//
//	Screen(pos ht, pos wd, char c) : m_height(ht), m_width(wd), m_contents(ht* wd, c) {}
//	char get() const 
//		{ return m_contents[m_cursor]; }
//	inline char get(pos ht, pos wd) const;
//	Screen& move(pos r, pos c);
//	Screen& display(ostream& os);
//	Screen& set(char c);
//private:
//	pos m_cursor = 0;
//	pos m_height = 0, m_width = 0;
//	string m_contents;
//};
//
//Screen& Screen::move(pos r, pos c)
//{
//	m_cursor = r * m_width + c;
//	return *this;
//}
//
//Screen& Screen::display(ostream& os) {
//	os << m_contents;
//	return *this;
//}
//
//inline char Screen::get(pos ht, pos wd) const
//{
//	return m_contents[ht * m_width + wd];
//}
//
//Screen& Screen::set(char c)
//{
//	m_contents[m_cursor] = c;
//	return *this;
//}
//
//int main() {
//	Screen myScreen(5, 5, 'X');
//	myScreen.move(4, 0).set('#').display(cout);
//	cout << endl;
//	myScreen.display(cout);
//	cout << endl;
//
//	return 0;
//}
//
//
//
