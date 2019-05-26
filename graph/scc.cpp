void dfs(int u) {
  static int t;
  static bool ins[N];
  static stack<int> stk;
  low[u] = dfn[u] = ++t;
  ins[u] = true;
  stk.push(u);
  for (Edge* p = g[u]; p; p = p->next) {
    if (!dfn[p->v])
      dfs(p->v);
    if (ins[p->v])
      low[u] = min(low[u], low[p->v]);
  }
  if (low[u] == dfn[u]) {
    int v;
    ++scn;
    do {
      v = stk.top();
      stk.pop();
      ins[v] = false;
      low[v] = low[u];
    } while (v != u);
  }
}
