//#include <iostream>
//#include <map>
//#include <vector>
//#include <algorithm>
//
//class RecurseDp {
//public:
//	int fib(int n) {
//		if (n < 2) return 1;
//		return fib(n - 1) + fib(n - 2);
//	}
//
//	int fib1(int n) {
//		if (n < 2) return 1;
//		if (m.find(n) != m.end()) return m[n];
//		int res = fib(n - 1) + fib(n - 2);
//		m[n] = res;
//		return res;
//	}
//
//	int fib2(int n) {
//		std::vector<int> memo(n + 1, 0);
//		memo[0] = 1, memo[1] = 1;
//		for (int i = 2; i <= n; i++) {
//			memo[i] = memo[i - 1] + memo[i - 2];
//		}
//		return memo.back();
//	}
//
//	int traverse(std::vector<std::vector<int>>& triangle, int n, int i, int j) {
//		if (i >= n - 1) return 0;
//		int l = traverse(triangle, n, i + 1, j) + triangle[i + 1][j];
//		int r = traverse(triangle, n, i + 1, j + 1) + triangle[i + 1][j + 1];
//		return std::min(l, r);
//	}
//	int minPathSumOfTriangle(std::vector<std::vector<int>>& triangle) {
//		return triangle[0][0] + traverse(triangle, triangle.size(), 0, 0);
//	}
//
//	int minPathSumOfTriangle1(std::vector<std::vector<int>>& triangle) {
//		return [](auto tmp) {
//			int n = tmp.size();
//			for (int i = 1; i < n; i++) {
//				tmp[i][0] += tmp[i - 1][0];
//				tmp[i][i] += tmp[i - 1][i - 1];
//				for (int j = 1; j < i; j++) {
//					tmp[i][j] += std::min(tmp[i - 1][j - 1], tmp[i - 1][j]);
//				}
//			}
//			return *min_element(tmp[n - 1].begin(), tmp[n - 1].end());
//		}(triangle);
//	}
//
//private:
//	std::map<int, int> m;
//};
//
//int main() {
//	auto rd = RecurseDp();
//	std::cout << rd.fib(20) << std::endl;
//	std::cout << rd.fib1(20) << std::endl;
//	std::cout << rd.fib2(20) << std::endl;
//
//	std::vector<std::vector<int>> triangle = {
//		{2}, {3,4}, {6,5,7}, {4,1,8,3}
//	};
//	std::cout << rd.minPathSumOfTriangle(triangle) << std::endl;
//	std::cout << rd.minPathSumOfTriangle1(triangle) << std::endl;
//	return 0;
//}