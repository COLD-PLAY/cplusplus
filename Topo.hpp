
#ifndef TEST_TOPO_H
#define TEST_TOPO_H

#include <cstring>

#include <vector>

struct Edge {
	int f_, t_, w_;
	Edge(int f, int t) : f_(f), t_(t), w_(1) {}
};

class Topo {
public:
	Topo(std::vector<Edge>& edges, int n) : n_(n), t_(n) {
		memset(graph_, 0, sizeof(graph_));
		memset(vis_, 0, sizeof(vis_));
		memset(topo_, 0, sizeof(topo_));
		for (auto& edge : edges) {
			graph_[edge.f_][edge.t_] = edge.w_;
		}
	}

	bool Sort() {
		for (int u = 0; u < n_; u++) if (!vis_[u])
			if (!Dfs(u)) return false;
		return true;
	}
	bool Sort_() { // 不用dfs也可以，就需要入度
		int i = 0;
		queue<int> que; // 利用队列完成拓扑排序
		for (int u = 0; u < n_; ++u) if (!indegree_[u])
			que.push(u);
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			for (int v = 0; v < n_; ++v) if (graph_[u][v]) {
				--indegree_[v];
				if (!indegree_[v])
					que.push(v);
			}
		}
		// while (i < n_) {
		//     for (int u = 0; u < n_; ++u) {
		//         if (!vis_[u] && !indegree_[u]) {
		//             topo_[i++] = u;
		//             for (int v = 0; v < n_; ++v) if (graph_[u][v]) {
		//                 --indegree_[v];
		//             }
		//             vis_[u] = 1;
		//         }
		//     }
		// }
	}
	void show() { // 打印结果
		for (auto& x : topo_)
			cout << x << ',';
		cout << endl;
	}

public:
	static const int MAXNUM = 10005;
	int graph_[MAXNUM][MAXNUM];
	int vis_[MAXNUM]; // -1表示正在访问、0表示未访问、1表示已访问
	int indegree_[MAXNUM];
	int topo_[MAXNUM]; // 最后的排序结果
	int n_, t_;

	bool Dfs(int u) { // 精髓，返回false表示有环
		vis_[u] = -1;
		for (int v = 0; v < n_; v++) if (graph_[u][v]) {
			if (vis_[v] == -1) return false;
			else if (!vis_[v] && !Dfs(v)) return false;
		}
		vis_[u] = 1; topo_[--t_] = u; // nb
		return true;
	}
};


// 找最长路径
int findLongestPath(vector<Edge>& edges, int n) {
	Topo topo(edges, n);
	topo.Sort();
	topo.show();
	vector<int> dp(n, 0);
	// 按照拓扑排序的结果 topo.topo_ 逆序进行动态规划数组的更新;
	int ans = 0;
	for (int i = n - 1; i >= 0; --i) {
		int u = topo.topo_[i];
		for (int v = 0; v < n; ++v) if (topo.graph_[u][v]) {
			dp[u] = max(dp[u], dp[v] + topo.graph_[u][v]);
		}
		ans = max(ans, dp[u]);
	}
}


#endif
