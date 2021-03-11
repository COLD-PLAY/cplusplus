#include "KMP.hpp"
#include "Sort.hpp"
#include "LRU.hpp"
#include "LFU.hpp"
#include "NaiveFunction.hpp"
#include "Topo.hpp"
#include "SegmentTree.hpp"
#include "Palindrome.hpp"
#include "threadpool.hpp"
#include "mythreadpool.hpp"
#include "mythread.hpp"
#include "Skiplist.hpp"
#include "AVLTree.hpp"

#include <string>

namespace kmptest {
void testKmp() {
	KMP_ kmp("mississippi", "issip");
	kmp.getNext();
	kmp.showNext();
	cout << kmp.match();
}
}

namespace sorttest {
void testSort() {
	Sort sort;
	auto start = clock();
	sort.SORT(100);
	auto end = clock();
	auto usetime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "total time: " << usetime * 1000 << "ms" << endl;
}
}

namespace lrutest {
void testLru() {
	auto lru = new LRUCache___(2);
	lru->put(1, 1); cout << "null" << endl;
	lru->put(2, 2); cout << "null" << endl;
	cout << lru->get(1) << endl;
	lru->put(3, 3); cout << "null" << endl;
	cout << lru->get(2) << endl;
	lru->put(4, 4); cout << "null" << endl;
	cout << lru->get(1) << endl;
	cout << lru->get(3) << endl;
	cout << lru->get(4) << endl;
}
}

namespace lfutest {
void testLfu() {
	auto lfu = new LFUCache_(2);
	lfu->put(1, 1); cout << "null" << endl;
	lfu->put(2, 2); cout << "null" << endl;
	cout << lfu->get(1) << endl;
	lfu->put(3, 3); cout << "null" << endl;
	cout << lfu->get(2) << endl;
	lfu->put(4, 4); cout << "null" << endl;
	cout << lfu->get(1) << endl;
	cout << lfu->get(3) << endl;
	cout << lfu->get(4) << endl;
}
}

namespace naivefuntiontest {
void func() {
	cout << "func" << endl;
}

struct functor {
	void operator()() {
		cout << "functor" << endl;
	}
};

void testNaiveFunction() {
	naive_function<void()> f;
	f = func;
	f();
	f = functor();
	f();
	f = []() { cout << "lambda" << endl; };
	f();
}
}

namespace segtreetest {
void testSegTree() {

}
}

namespace palindrometest {
void testPalindrome() {
	string s("aababaaaccccaaaabbbbabaaaaaaaaaaccbbaa");
	Palindrome p(s);
	cout << p.isPalindrome(1, 3);
}
}

namespace virtualinherittest {
void testVirtualInherit() {
	class A {
	private:
		int a;
	public:
		A(int _a) : a(_a) {}
		virtual void f() {}
		virtual void g() {}
		virtual void h() {}
	};

	class B : public A {
	private:
		int b;
	public:
		B(int _a, int _b) : b(_b), A(_a) {}
	};
}
}

namespace threadpooltest
{
void fun1(int slp) {
	cout << " hello, fun1 ! " << this_thread::get_id() << endl;
	if (slp > 0) {
		cout << "============ fun1 sleep " << slp << " =========== " << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::milliseconds(slp));
		// Sleep(slp);
	}
}

struct gfun {
	int operator()(int n) {
		cout << n << " hello, gfun ! " << this_thread::get_id() << endl;
		return 42;
	}
};

class A {
public:
	static int Afun(int n = 0) {
		cout << n << " hello, Afun ! " << this_thread::get_id() << endl;
		return n;
	}

	static string Bfun(int n, string str, char c) {
		cout << n << " hello, Bfun ! " << str.c_str() << " " << int(c) << " " << this_thread::get_id() << endl;
		return str;
	}
};

int main() {
	try {
		threadpool tp{ 50 };
		A a;
		future<void> ff = tp.commit(fun1, 42);
		future<int> fg = tp.commit(gfun{}, 42);
		future<int> gg = tp.commit(a.Afun, 42); // ide 提示错误？但可以编译运行
		future<string> gh = tp.commit(a.Bfun, 42, "42", 42);
		future<string> fh = tp.commit([]() -> string {
			cout << " hello, fh ! " << this_thread::get_id() << endl;
			return "hello, fh ret!";
			});

		cout << " ======= sleep ======= " << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::milliseconds(42));

		for (int i = 0; i < 50; ++i) {
			tp.commit(fun1, i * 42);
		}

		cout << " ======= commit all ====== " << this_thread::get_id() << " idlsize = " << tp.idlCount() << endl;

		cout << " ======= sleep ======= " << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::seconds(3));

		ff.get(); // 调用.get()获取返回值会等待线程执行完，获取返回值
		cout << fg.get() << " " << fh.get().c_str() << " " << this_thread::get_id() << endl;

		cout << " =======  sleep ========= " << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::seconds(3));

		cout << " =======  fun1,55 ========= " << this_thread::get_id() << endl;
		tp.commit(fun1, 55).get();    //调用.get()获取返回值会等待线程执行完

		cout << "end... " << this_thread::get_id() << endl;


		threadpool pool(4);
		vector<future<int>> results;

		for (int i = 0; i < 8; ++i) {
			results.emplace_back(
				pool.commit([i] {
					cout << "hello " << i << endl;
					this_thread::sleep_for(chrono::seconds(1));
					cout << "world " << i << endl;
					return i * i;
					})
			);
		}
		cout << " =======  commit all2 ========= " << this_thread::get_id() << endl;

		for (auto&& result : results)
			cout << result.get() << ' ';
		cout << endl;
	}
	catch (exception& e) {
		cout << "some unhappy happened...  " << this_thread::get_id() << e.what() << endl;
	}
	return 0;
}
}

namespace threadtest {
void threadtest() {
	mythread thread;
	thread.threadTest();
}
}

namespace skiplisttest {
void skiplisttest() {
	Skiplist_ sk;
	sk.add(1);
	sk.add(2);
	sk.add(3);
	cout << sk.search(0) << endl;
	//sk.add(4);
}
}

namespace avltreetest {
void testavltree()
{
	AVLTree<int> avl;
	for (int i = 0; i < 50; i++)
		avl.insert(i);
	cout << "树高：" << avl.height() << endl;

	cout << "中序遍历:" << endl;
	avl.inOrder();
	cout << endl;

	cout << "删除元素10" << endl;
	avl.remove(10);

	auto b = avl.searchIterator(10);

	if (b != nullptr)
		cout << b->key;
	else
		cout << "无此元素" << endl;
	
	b = avl.searchIterator(15);
	if (b) cout << b->key << endl;
}
}

int main() {
	//sorttest::testSort();
	//kmptest::testKmp();
	//lrutest::testLru();
	//lfutest::testLfu();
	//naivefunctiontest::testNaiveFunction();
	//segtreetest::testSegTree();
	//palindrometest::testPalindrome();
	//virtualinherittest::testVirtualInherit();
	//threadpooltest::main();
	//threadtest::threadtest();
	//skiplisttest::skiplisttest();
	avltreetest::testavltree();

	return 0;
}
