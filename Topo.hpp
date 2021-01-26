
#ifndef TEST_TOPO_H
#define TEST_TOPO_H

#include <cstring>

#include <vector>

class Topo {
public:
	struct Edge {
		int f_, t_, w_;
		Edge(int f, int t) : f_(f), t_(t), w_(1) {}
	};
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

private:
	static const int MAXNUM = 10005;
	int graph_[MAXNUM][MAXNUM];
	int vis_[MAXNUM]; // -1, 0, 1
	int topo_[MAXNUM];
	int n_, t_;

	bool Dfs(int u) {
		vis_[u] = -1;
		for (int v = 0; v < n_; v++) if (graph_[u][v]) {
			if (vis_[v] == -1) return false;
			else if (!vis_[v] && !Dfs(v)) return false;
		}
		vis_[u] = 1; topo_[--t_] = u;
		return true;
	}
};

#endif
