#include "KMP.hpp"

#include "Sort.hpp"

void testKmp() {
	KMP kmp("liaozhou", "iaoz");
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

int main() {
	//testSort();
	testKmp();
}

