#include "KMP.hpp"
#include "Sort.hpp"
#include "LRU.hpp"
#include "LFU.hpp"
#include "NaiveFunction.hpp"
#include "Topo.hpp"
#include "SegmentTree.hpp"
#include "Palindrome.hpp"

void testKmp() {
	KMP_ kmp("mississippi", "issip");
	kmp.getNext();
	kmp.showNext();
	cout << kmp.match();
}

void testSort() {
	Sort sort;
	auto start = clock();
	sort.SORT(100);
	auto end = clock();
	auto usetime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "total time: " << usetime * 1000 << "ms" << endl;
}

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

void func() {
	std::cout << "func" << std::endl;
}

struct functor {
	void operator()() {
		std::cout << "functor" << std::endl;
	}
};

void testNaiveFunction() {
	naive_function<void()> f;
	f = func;
	f();
	f = functor();
	f();
	f = []() { std::cout << "lambda" << std::endl; };
	f();
}

void testSegTree() {

}

void testPalindrome() {
	string s("aababaaaccccaaaabbbbabaaaaaaaaaaccbbaa");
	Palindrome p(s);
	std::cout << p.isPalindrome(1, 3);
}

int main() {
	//testSort();
	testKmp();
	//testLru();
	//testLfu();
	//testNaiveFunction();
	//testSegTree();
	testPalindrome();

	return 0;
}
