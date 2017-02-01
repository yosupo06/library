/*
https://gist.github.com/snuke/df5d66a2adb575228c96

AとBは必ず同じサイクルに含まれる で分解したもの ちゃんと同値関係になっている
橋検出の際のimos法っぽいことをやるときに、足す値を乱数にして、それが一致するものが同じグループ
llだと危険そう?
*/

class ToursDecomposition {
 public:
  struct Edge {
    int u, v;
    Edge() {}
    Edge(int u, int v) : u(u), v(v) {}
  };
  int n;
  vector< vector<int> > to;
  vector<int> depth;
  vector<ll> hash;
  map< ll, vector<Edge> > group;
  ToursDecomposition() {}
  ToursDecomposition(int n) : n(n), to(n), depth(n, -1), hash(n) {}
  void AddEdge(int u, int v) {
    to[u].push_back(v);
    to[v].push_back(u);
  }
  void Init() {
    rep(i,n) {
      if (depth[i] != -1) continue;
      depth[i] = 0;
      dfs(i, -1);
    }
  }
 private:
  void dfs(int v, int p) {
    for (int u : to[v]) {
      if (depth[u] == -1) {
        depth[u] = depth[v] + 1;
        dfs(u, v);
        hash[v] += hash[u];
        group[hash[u]].push_back(Edge(u, v));
      } else if (depth[u] < depth[v] && u != p) {
        ll r = rand();
        group[r].push_back(Edge(u, v));
        hash[v] += r;
        hash[u] -= r;
      }
    }
  }
};