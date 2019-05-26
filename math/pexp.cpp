typedef long long ll;

const int P = 998244353, R = 3;
const int L = 20, N = 1 << L;

int brev[N], invt[N];

int norm(int x) { return x >= P ? x - P : x; }

int mpow(int x, int k) {
  int ret = 1;
  while (k) {
    if (k & 1)
      ret = ret * (ll)x % P;
    k >>= 1;
    x = x * (ll)x % P;
  }
  return ret;
}

int inv(int a) { return mpow(a, P - 2); }

void prepare(int n) {
  invt[1] = 1;
  for (int i = 2; i <= n; ++i)
    invt[i] = -(P / i) * (ll)invt[P % i] % P + P;
}

void ntt(int* a, int lgn, int sgn) {
  int n = 1 << lgn;
  for (int i = 1; i < n; ++i)
    brev[i] = brev[i >> 1] >> 1 | (i & 1) << (lgn - 1);
  for (int i = 0; i < n; ++i)
    if (i < brev[i])
      swap(a[i], a[brev[i]]);
  int r = sgn == 1 ? R : inv(R);
  for (int i = 0; i < lgn; ++i) {
    int t = 1 << i, omega = mpow(r, (P - 1) >> (i + 1));
    for (int j = 0; j < n; j += t << 1) {
      int w = 1;
      for (int k = 0; k < t; ++k) {
        int a0 = a[j + k], a1 = a[j + k + t];
        a[j + k] = (a0 + a1 * (ll)w) % P;
        a[j + k + t] = (a0 + a1 * (ll)(P - w)) % P;
        w = w * (ll)omega % P;
      }
    }
  }
  if (sgn == -1) {
    int in = inv(n);
    for (int i = 0; i < n; ++i)
      a[i] = a[i] * (ll)in % P;
  }
}

void conv(const int* a, const int* b, int* c, int n, int m) {
  static int ta[N], tb[N];
  int nn = n + m, l = 0;
  while ((1 << l) <= nn)
    ++l;
  memset(ta, 0, sizeof(int) << l);
  memset(tb, 0, sizeof(int) << l);
  memcpy(ta, a, sizeof(int) * (n + 1));
  ntt(ta, l, 1);
  if (a == b)
    memcpy(tb, ta, sizeof(int) << l);
  else {
    memcpy(tb, b, sizeof(int) * (m + 1));
    ntt(tb, l, 1);
  }
  for (int i = 0; i < 1 << l; ++i)
    ta[i] = ta[i] * (ll)tb[i] % P;
  ntt(ta, l, -1);
  memcpy(c, ta, sizeof(int) * (n + m + 1));
}

void pinv(const int* a, int* b, int n) {
  static int tmp[N], tt[N], ta[N];
  int lgn = 0;
  while (1 << lgn <= n) ++lgn;
  memset(tmp, 0, sizeof(int) << (lgn + 1));
  tmp[0] = inv(a[0]);
  for (int i = 0; i < lgn; ++i) {
    memset(tt, 0, sizeof(int) << (i + 2));
    memset(ta, 0, sizeof(int) << (i + 2));
    memcpy(tt, tmp, sizeof(int) << i);
    memcpy(ta, a, sizeof(int) << (i + 1));
    ntt(tt, i + 2, 1);
    ntt(ta, i + 2, 1);
    for (int j = 0; j < 1 << (i + 2); ++j)
      tmp[j] = (P + 2 - ta[j] * (ll)tt[j] % P) * (ll)tt[j] % P;
    ntt(tmp, i + 2, -1);
    memset(tmp + (1 << (i + 1)), 0, sizeof(int) << (i + 1));
  }
  memcpy(b, tmp, sizeof(int) * (n + 1));
}

void pder(const int* a, int* b, int n) {
  for (int i = 0; i < n; ++i)
    b[i] = a[i + 1] * (ll)(i + 1) % P;
  b[n] = 0;
}

void pint(const int* a, int* b, int n) {
  for (int i = n; i; --i)
    b[i] = a[i - 1] * (ll)invt[i] % P;
  b[0] = 0;
}

void pln(const int* a, int* b, int n) {
  static int t1[N], t2[N];
  pder(a, t1, n);
  pinv(a, t2, n);
  conv(t1, t2, t2, n, n);
  pint(t2, b, n);
}

void pexp(const int* a, int* b, int n) {
  static int tmp[N], tx[N];
  int lgn = 0;
  while (1 << lgn <= n) ++lgn;
  memset(tmp, 0, sizeof(int) << lgn);
  tmp[0] = 1;
  for (int i = 0; i < lgn; ++i) {
    pln(tmp, tx, (1 << (i + 1)) - 1);
    for (int j = 1; j < 1 << (i + 1); ++j)
      tx[j] = norm(P - tx[j] + a[j]);
    tx[0] = 1;
    conv(tx, tmp, tmp, (1 << (i + 1)) - 1, (1 << (i + 1)) - 1);
    memset(tmp + (1 << (i + 1)), 0, sizeof(int) << (i + 1));
  }
  memcpy(b, tmp, sizeof(int) * (n + 1));
}
