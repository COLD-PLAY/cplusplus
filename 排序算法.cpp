#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

void bubbleSort(vector<int>& arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		bool flag = true;
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				flag = false;
			}
		}
		if (flag) break;
	}
}

void selectionSort(vector<int>& arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		int minidx = i;
		for (int j = i; j < n; j++) {
			if (arr[minidx] > arr[j]) minidx = j;
		}
		swap(arr[i], arr[minidx]);
	}
}

void insertSort(vector<int>& arr, int n) {
	for (int i = 1; i < n; i++) {
		int j = i, k = arr[i];
		while (j && k < arr[j - 1]) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = k;
	}
}

void shellSort(vector<int>& arr, int n) {
	int h = 1;
	while (h < n / 3) {
		h = h * 3 + 1;
	}
	while (h > 0) {
		for (int i = h; i < n; i++) {
			int j = i, k = arr[i];
			while (j >= h && k < arr[j - h]) {
				arr[j] = arr[j - h];
				j -= h;
			}
			arr[j] = k;
		}
		h /= 3;
	}
}

void merge(vector<int>& arr, int l, int m, int h) {
	vector<int> brr(h - l + 1, 0);
	int k = 0;
	int l1 = l, l2 = m + 1;
	int h1 = m, h2 = h;
	while (l1 <= h1 && l2 <= h2)
		brr[k++] = arr[l1] < arr[l2] ? arr[l1++] : arr[l2++];
	while (l1 <= h1) brr[k++] = arr[l1++];
	while (l2 <= h2) brr[k++] = arr[l2++];
	for (int i = 0; i < k; i++)
		arr[l + i] = brr[i];
}
void mergeSort(vector<int>& arr, int l, int h) {
	if (l >= h) return;
	int m = l + (h - l) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, h);
	merge(arr, l, m, h);
}
void mergeSort_iter(vector<int>& arr, int n) {
	vector<int> brr(n, 0);
	for (int seg = 1; seg < n; seg *= 2) {
		for (int start = 0; start < n; start += seg * 2) {
			int l = start, m = min(l + seg, n), h = min(m + seg, n);
			int l1 = l, l2 = m;
			int h1 = m, h2 = h;

			int k = l;
			while (l1 < h1 && l2 < h2)
				brr[k++] = arr[l1] < arr[l2] ? arr[l1++] : arr[l2++];
			while (l1 < h1) brr[k++] = arr[l1++];
			while (l2 < h2) brr[k++] = arr[l2++];
		}
		for (int i = 0; i < n; i++) arr[i] = brr[i];
	}
}

void quickSort(vector<int>& arr, int l, int h) {
	if (l >= h) return;
	int pivot = arr[l];
	int tl = l, th = h;
	while (tl < th) {
		while (arr[th] >= pivot && tl < th) th--;
		while (arr[tl] <= pivot && tl < th) tl++;
		swap(arr[tl], arr[th]);
	}
	swap(arr[l], arr[tl]);
	
	quickSort(arr, l, tl - 1);
	quickSort(arr, tl + 1, h);
}
void quickSort_iter(vector<int>& arr, int n) {
	vector<pair<int, int>> st;
	st.push_back({ 0, n - 1 });
	while (!st.empty()) {
		auto& range = st.back();
		st.pop_back();
		int l = range.first, h = range.second;
		if (l >= h) continue;
		int pivot = arr[l];
		int tl = l, th = h;
		while (tl < th) {
			while (arr[th] >= pivot && tl < th) th--;
			while (arr[tl] <= pivot && tl < th) tl++;
			swap(arr[tl], arr[th]);
		}
		swap(arr[l], arr[tl]);

		st.push_back({ l, tl - 1 });
		st.push_back({ tl + 1, h });
	}
}

void maxHeapify(vector<int>& arr, int s, int e) {
	int fa = s, son = fa * 2 + 1;
	while (son <= e) {
		if (son + 1 <= e && arr[son] < arr[son + 1]) son++;
		if (arr[fa] >= arr[son]) return;
		else {
			swap(arr[fa], arr[son]);
			fa = son, son = fa * 2 + 1;
		}
	}
}
void heapSort(vector<int>& arr, int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		maxHeapify(arr, i, n - 1);
	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		maxHeapify(arr, 0, i - 1);
	}
}

void countingSort(vector<int>& arr, int n) {
	int minv, maxv; minv = maxv = arr[0];
	for (auto& x : arr) maxv = max(maxv, x), minv = min(minv, x);
	int diff = maxv - minv;
	vector<int> cnt(diff + 5, 0);
	for (auto& x : arr) cnt[x - minv]++;
	int k = 0;
	for (int i = 0; i < cnt.size(); i++)
		for (int j = 0; j < cnt[i]; j++)
			arr[k++] = i + minv;
}

void bucketSort(vector<int>& arr, int n) {
	int minv, maxv; minv = maxv = arr[0];
	for (auto& x : arr) maxv = max(maxv, x), minv = min(minv, x);
	int bnum = (maxv - minv) / n + 1;
	vector<vector<int>> bucket(bnum);
	for (auto& x : arr) bucket[(x - minv) / n].push_back(x);
	int k = 0;
	for (int i = 0; i < bnum; i++) {
		sort(bucket[i].begin(), bucket[i].end());
		for (auto& x : bucket[i])
			arr[k++] = x;
	}
}

void radixSort(vector<int>& arr, int n) {
	int minv, maxv; minv = maxv = arr[0];
	for (auto& x : arr) maxv = max(maxv, x), minv = min(minv, x);
	int bnum = (maxv - minv) / 10 + 1;
	vector<vector<int>> bucket(bnum);
	for (auto& x : arr) bucket[(x - minv) / 10].push_back(x);
	int k = 0;
	for (int i = 0; i < bnum; i++) {
		sort(bucket[i].begin(), bucket[i].end());
		for (auto& x : bucket[i])
			arr[k++] = x;
	}
}

vector<int> generateRandomArray(int n, int l, int h) {
	vector<int> arr;

	srand(time(NULL));
	for (int i = 0; i < n; i++)
		arr.push_back(rand() % (h - l + 1) + l);
	return arr;
}

void SORT(int times) {
	for (int i = 0; i < times; i++) {
		vector<int> arr = generateRandomArray(20, 1, 50);
		for (auto& x : arr) cout << x << ','; cout << endl;
		//bubbleSort(arr, arr.size()); // 17755
		//selectionSort(arr, arr.size()); // 7554
		//insertSort(arr, arr.size()); // 5927
		//shellSort(arr, arr.size()); // 295
		//mergeSort(arr, 0, arr.size() - 1); // 1005
		//mergeSort_iter(arr, arr.size()); // 350
		//quickSort(arr, 0, arr.size() - 1); // 230
		//quickSort_iter(arr, arr.size()); // 361
		heapSort(arr, arr.size()); // 478
		//countingSort(arr, arr.size()); // 170
		//bucketSort(arr, arr.size()); // 360
		//radixSort(arr, arr.size()); // 470
		for (auto& x : arr) cout << x << ','; cout << endl;
	}
}

int main() {
	auto start = clock();
	SORT(100);
	auto end = clock();
	auto usetime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "total time: " << usetime * 1000 << "ms" << endl;

	return 0;
}