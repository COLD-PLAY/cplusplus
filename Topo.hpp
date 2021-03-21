
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
	bool Sort_() { // ����dfsҲ���ԣ�����Ҫ���
		int i = 0;
		queue<int> que; // ���ö��������������
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
	void show() { // ��ӡ���
		for (auto& x : topo_)
			cout << x << ',';
		cout << endl;
	}

public:
	static const int MAXNUM = 10005;
	int graph_[MAXNUM][MAXNUM];
	int vis_[MAXNUM]; // -1��ʾ���ڷ��ʡ�0��ʾδ���ʡ�1��ʾ�ѷ���
	int indegree_[MAXNUM];
	int topo_[MAXNUM]; // ����������
	int n_, t_;

	bool Dfs(int u) { // ���裬����false��ʾ�л�
		vis_[u] = -1;
		for (int v = 0; v < n_; v++) if (graph_[u][v]) {
			if (vis_[v] == -1) return false;
			else if (!vis_[v] && !Dfs(v)) return false;
		}
		vis_[u] = 1; topo_[--t_] = u; // nb
		return true;
	}
};


// ���·��
int findLongestPath(vector<Edge>& edges, int n) {
	Topo topo(edges, n);
	topo.Sort();
	topo.show();
	vector<int> dp(n, 0);
	// ������������Ľ�� topo.topo_ ������ж�̬�滮����ĸ���;
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
