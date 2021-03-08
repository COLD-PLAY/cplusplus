
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1000000000;

class Dijkstra {
private:
	vector<vector<int>> graph;
	vector<int> dis;
	vector<bool> vis;
	int n, s;

public:
	Dijkstra(vector<vector<int>>& edges, int _n, int _s) : graph(_n, vector<int>(_n, -1))
		, dis(_n, INF), vis(_n, false), n(_n), s(_s) {
		for (auto& e : edges) {
			graph[e[0]][e[1]] = e[2];
			if (e[0] == s) dis[e[1]] = e[2];
		}
	}
	
	// 基础算法
	void solve() {
		dis[s] = 0;
		vis[s] = true;
		for (int i = 0; i < n - 1; ++i) {
			int u = -1;
			int MIN = INF;
			for (int j = 0; j < n; ++j) {
				if (vis[j] == false && dis[j] < MIN) {
					u = j;
					MIN = dis[j];
				}
			}
			// 找不到小于INF 的dis[u]，说明剩下的顶点与s不连通
			if (u == -1) return;
			vis[u] = true;
			for (int v = 0; v < n; ++v) {
				if (vis[v] == false &&
					graph[u][v] + dis[u] < dis[v]) {
					dis[v] = graph[u][v] + dis[u];
				}
			}
		}
		for (auto& d : dis) cout << d << ' '; cout << endl;
	}
	// 使用堆优化
	void solve_() {
		struct Node {
			int v, d;
			Node(int _v, int _d) : v(_v), d(_d) {}
			bool operator <(const Node& rhs) const {
				return d > rhs.d; // 大的在后面
			}
		};
		priority_queue<Node> que;
		que.push({ s, 0 });
		dis[s] = 0;
		while (que.size()) {
			auto node = que.top();
			que.pop();
			int u = node.v;
			int d = node.d;
			if (vis[u]) continue;
			vis[u] = true;
			dis[u] = d;
			for (int v = 0; v < n; ++v) {
				if (!vis[v] && graph[u][v] != -1) {
					que.push({ v, d + graph[u][v] });
				}
			}
		}
		for (auto& d : dis) cout << d << ' '; cout << endl;
	}
	// 使用堆优化 + Pair
	void solve__() {
		typedef pair<int, int> Pair; // 小顶堆
		priority_queue<Pair, vector<Pair>, greater<Pair>> que;
		que.push({ 0, s });
		dis[s] = 0;
		while (que.size()) {
			auto node = que.top();
			que.pop();
			int u = node.second;
			int d = node.first;
			if (vis[u]) continue;
			vis[u] = true;
			dis[u] = d;
			for (int v = 0; v < n; ++v) {
				if (!vis[v] && graph[u][v] != -1) {
					que.push({ d + graph[u][v], v });
				}
			}
		}
		for (auto& d : dis) cout << d << ' '; cout << endl;
	}
};

