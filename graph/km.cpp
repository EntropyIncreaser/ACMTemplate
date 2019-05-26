const int N = 810;

int n, nl, nr, g[N][N];
int slack[N], sl[N], sr[N], pre[N], match[N];
bool vis[N];
ll ans;

void bfs(int S) {
  memset(slack, 127, sizeof(slack));
  memset(vis, 0, sizeof(vis));
  memset(pre, 0, sizeof(pre));
  int u, nt, d, nw;
  match[u = 0] = S;
  while (match[u]) {
    nw = match[u];
    d = slack[0];
    vis[u] = true;
    for (int v = 1; v <= n; ++v)
      if (!vis[v]) {
        if (sl[nw] + sr[v] - g[nw][v] < slack[v])
          slack[v] = sl[nw] + sr[v] - g[nw][v], pre[v] = u;
        if (d > slack[v])d = slack[v], nt = v;
      }
    sl[match[0]] -= d;
    for (int i = 1; i <= n; ++i)
      if (vis[i])sl[match[i]] -= d, sr[i] += d;
      else slack[i] -= d;
    u = nt;
  }
  while (u)
    match[u] = match[pre[u]], u = pre[u];
}

void km() {
  for (int i = 1; i <= nl; ++i)
    sl[i] = *max_element(g[i] + 1, g[i] + nr + 1);
  for (int i = 1; i <= nl; ++i)
    bfs(i);
}

int main() {
  int m;
  scanf("%d%d%d", &nl, &nr, &m);
  n = max(nl, nr) << 1;
  while (m--) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    g[u][v] = w;
  }
  km();
  for (int i = 1; i <= n; ++i)
    ans += sl[i] + sr[i];
  printf("%lld\n", ans);
  memset(pre, 0, sizeof(pre));
  for (int i = 1; i <= n; ++i)
    pre[match[i]] = i;
  for (int i = 1; i <= nl; ++i)
    printf("%d ", g[i][pre[i]] ? pre[i] : 0);

  return 0;
}
