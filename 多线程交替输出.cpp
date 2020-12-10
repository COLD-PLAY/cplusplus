//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//#include <windows.h>
//
//using namespace std;
//
//mutex mtx;
//condition_variable cond1, cond2;
//
//void coutNum() {
//	for (int i = 1; i <= 26; i++) {
//		unique_lock<mutex> locker(mtx);
//		cout << i;
//		cond2.notify_one();
//		cond1.wait(locker);
//		locker.unlock();
//	}
//}
//
//void coutAlp() {
//	Sleep(1);
//	for (int i = 0; i < 26; i++) {
//		unique_lock<mutex> locker(mtx);
//		cout << char('a' + i);
//		cond1.notify_one();
//		cond2.wait(locker);
//	}
//}
//
//int main() {
//	auto p1 = new thread(coutNum);
//	auto p2 = new thread(coutAlp);
//	p1->join();
//	p2->join();
//
//	return 0;
//}