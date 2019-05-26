struct { int a, b, id; } p[N], q[N];

int sa[N], rk[N], cnt[N], ht[N];
char s[N];

void buildsa(int n) {
  for (int i = 1; i <= n; ++i) cnt[s[i] - 'a' + 1] = 1;
  for (int i = 1; i <= 26; ++i) cnt[i] += cnt[i - 1];
  for (int i = 1; i <= n; ++i) rk[i] = cnt[s[i] - 'a' + 1];
  for (int t = 1; t < n; t <<= 1) {
    for (int i = 1; i <= n; ++i) {
      p[i].a = rk[i];
      p[i].b = (i + t) > n ? 0 : rk[i + t];
      p[i].id = i;
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; ++i) ++cnt[p[i].b];
    for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
    for (int i = n; i; --i) q[cnt[p[i].b]--] = p[i];
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; ++i) ++cnt[q[i].a];
    for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
    for (int i = n; i; --i) p[cnt[q[i].a]--] = q[i];
    int cc = 0;
    for (int i = 1; i <= n; ++i) {
      if (p[i - 1].a != p[i].a || p[i - 1].b != p[i].b) ++cc;
      rk[p[i].id] = cc;
    }
    if (cc == n) break;
  }
  for (int i = 1; i <= n; ++i) sa[rk[i]] = i;
  int h = 0;
  for (int i = 1; i <= n; ++i) {
    if (h) --h;
    while (s[i + h] == s[sa[rk[i] + 1] + h]) ++h;
    ht[rk[i]] = h;
  }
}
