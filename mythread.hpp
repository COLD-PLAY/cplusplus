
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <string>
#include <functional>

using namespace std;

class mythread {
private:
	thread _threads[8];
	mutex _lock;
	condition_variable _cv;
	int tmp{ 0 };

public:
	mythread() {}
	~mythread() {
		_cv.notify_all();
		for (auto& thread : _threads) {
			break;
			if (thread.joinable())
				thread.join();
		}
	}

	static void func(string str) {
		cout << "hello, " << str << " this is " << this_thread::get_id() << endl;
	}

	void threadTest() {
		//_threads[0] = thread(func);
		for (int i = 0; i < 8; ++i) {
			unique_lock<mutex> lock{ _lock };
			_cv.wait(lock);
			_threads[i] = thread(func, to_string(i));
			//_threads[i] = thread([]() {
			//	cout << " this is " << this_thread::get_id() << endl;
			//	});

			_cv.notify_one();
		}
	}
};