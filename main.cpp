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
#include "Radix_Trie.hpp"

#include <map>
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

//const int a = 5;

namespace consttest { // 全局const 变量会被存到.rodata 只读空间（但是局部变量放到栈上的，拿到地址就可以随便改
void testconst() {
	const int a = 5;
	int* p = (int*)&a;
	cout << &a << ' ' << p << endl;
	*p = 10;
	cout << a << endl;
}
}

// pol: Principle of locality 局部性原理
// 没有对数组进行排序 会消耗18.572s
// 对数组进行排序后 只消耗6.754s
namespace poltest {
void testpol() {
	// Generate data
	const unsigned arraySize = 32768;
	int data[arraySize];

	for (unsigned c = 0; c < arraySize; ++c)
		data[c] = std::rand() % 256;

	// !!! With this, the next loop runs faster.
	//std::sort(data, data + arraySize);

	// Test
	clock_t start = clock();
	long long sum = 0;

	for (unsigned i = 0; i < 100000; ++i)
	{
		// Primary loop
		for (unsigned c = 0; c < arraySize; ++c)
		{
			if (data[c] >= 128)
				sum += data[c];
		}
	}

	double elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;

	std::cout << elapsedTime << std::endl;
	std::cout << "sum = " << sum << std::endl;
}
}

namespace endiantest {
void testendian() {
	int a = 0x12345678;
	// 1. 直接指针
	char* p = (char*)&a;
	if (*p == 0x78)
		cout << "little endian" << endl;
	else
		cout << "big endian" << endl;

	// 用一下联合体
	union Un {
		char c;
		int i;
	};

	Un un;
	un.i = 0x12345678;
	if (un.c == 0x78)
		cout << "little endian" << endl;
	else
		cout << "big endian" << endl;
}
}

namespace encrypttest {
void testencrypt() {
	string str, pass;
	string str_encrypted, str_decrypted;
	bool flag = false;
	cout << "输入加密/解密标志位：（1表示加密，0表示解密）"; cin >> flag;
	cout << "输入待加/解密字符串："; cin >> str;
	cout << "输入密钥字符串："; cin >> pass;
	int n = pass.size();
	str_encrypted = str;
	if (flag) { // 加密
		for (int i = 0; i < str.size(); ++i)
			str_encrypted[i] = str[i] + pass[i % n];
		cout << "加密后字符串：" << str_encrypted << endl;
	}
	else { // 解密
		try {
			for (int i = 0; i < str.size(); ++i)
				str_decrypted[i] = str[i] - pass[i % n];
			cout << "解密后字符串：" << str_decrypted << endl;
		}
		catch (...) {
			cout << "密钥错误！" << endl;
		}
	}
}
}

namespace addresstest {
void testaddress() {
	int t[3][2] = { {1,2},{3,4},{5,6} }, * pt[3], k;
	for (k = 0; k < 3; ++k)
		pt[k] = t[k];
	cout << *(&pt[2]) << endl;
}
}

namespace reversepolishnotationtest {
int testreversepolishnotation(char str[]) {
	int stack[10005];
	int top = 0;
	int len = strlen(str);
	for (int i = 0; i < len; ++i) {
		if (!isdigit(str[i])) {
			if (str[i] == ',')
				continue;
			int a = stack[--top];
			int b = stack[--top];
			int c;
			switch (str[i])
			{
			case '+':
				c = b + a;
				break;
			case '-':
				c = b - a;
				break;
			case '*':
				c = b * a;
				break;
			case '/':
				c = b / a;
				break;
			default:
				break;
			}
			stack[top++] = c;
		}
		int tmp = 0;
		bool flag = false;
		while (i < len && isdigit(str[i])) {
			flag = true;
			tmp *= 10, tmp += str[i] - '0';
			++i;
		}
		if (flag)
			stack[top++] = tmp; // 压栈
	}
	printf("%s = %d", str, stack[0]);
	return stack[0];
}
}

namespace fututest {
void divide() { // 没考虑到负数情况
	int a, b;
	cin >> a >> b;
	if (a % b == 0) {
		cout << a / b << endl;
		return;
	}
	int d = a / b;
	a %= b;
	unordered_map<int, bool> vis;
	vector<int> nums;
	while (a && !vis.count(a)) {
		vis[a] = true;
		a *= 10;
		nums.push_back(a / b);
		a %= b;
	}
	cout << d << '.';
	if (a == 0) {
		for (auto& x : nums)
			cout << x;
	}
	else {
		a = (a * 10) / b;
		bool flag = false;
		for (auto& x : nums) {
			if (x != a) cout << x;
			else cout << '(' << x;
		}
		cout << ')';
	}
	cout << endl;
}
}

namespace radixtrietest {
void testradixtrie() {
	Trie trie;
	cout << endl << "========================= trie ========================" << endl;
	trie.insert("java", 1234);
	trie.insert("javascript", 1354);
	trie.insert("just", 5723);
	trie.insert("liaozhou", 5164);
	trie.insert("liaofan", 6592);

	cout << "jav: " << trie.search("jav") << endl;
	cout << "java: " << trie.search("java") << endl;
	cout << "javascript: " << trie.search("javascript") << endl;

	cout << endl;

	trie.foreach([](string key, int val) { cout << key << ": " << val << endl; });

	cout << endl << "====================== radix tree ====================" << endl;
	RadixTree radixtree;
	radixtree.insert("java", 1234);
	radixtree.insert("javascript", 1354);
	radixtree.insert("just", 5723);
	radixtree.insert("liaozhou", 5164);
	radixtree.insert("liaofan", 6592);

	cout << "jav: " << radixtree.search("jav") << endl;
	cout << "java: " << radixtree.search("java") << endl;
	cout << "javascript: " << radixtree.search("javascript") << endl;

	cout << endl;

	radixtree.foreach([](string key, int val) { cout << key << ": " << val << endl; });
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
	//avltreetest::testavltree();
	//consttest::testconst();
	//poltest::testpol();
	//endiantest::testendian();
	//encrypttest::testencrypt();
	//addresstest::testaddress();
	//char str[] = "2,3,*";
	//reversepolishnotationtest::testreversepolishnotation(str);
	//fututest::divide();
	radixtrietest::testradixtrie();

	return 0;
}
