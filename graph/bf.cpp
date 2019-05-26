int n, bcn;
int prt[N], low[N], dfn[N];
E *g[N], *bg[N * 2];

int tm;
stack<int> stk;

void dfs(int u) {
  dfn[u] = low[u] = ++tm;
  stk.push(u);
  for (E* p = g[u]; p; p = p->next)
    if (!dfn[p->v]) {
      prt[p->v] = u;
      dfs(p->v);
      low[u] = min(low[u], low[p->v]);
      if (low[p->v] >= dfn[u]) {
        ++bcn;
        link(bg, bcn, u);
        int v;
        do {
          v = stk.top();
          stk.pop();
          link(bg, bcn, v);
        } while (p->v != v);
      }
    } else if (p->v != prt[u])
      low[u] = min(low[u], dfn[p->v]);
}
