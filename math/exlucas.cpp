void exGcd(int a, int b, int& x, int& y) {
  if (!b) {
    x = 1;
    y = 0;
    return;
  }
  exGcd(b, a % b, y, x);
  y -= a / b * x;
}

int inv(int a, int m) {
  int x, y;
  exGcd(a, m, x, y);
  if (x < 0)
    x += m;
  return x;
}

int crt(const vector<pair<int, int>>& group) {
  int m = 1, r = 0;
  for (const auto& pr : group) {
    int m1, r1;
    tie(m1, r1) = pr;
    int mm = m * m1, i, i1;
    i = m * (ll)inv(m, m1) % mm;
    i1 = m1 * (ll)inv(m1, m) % mm;
    r = (r * (ll)i1 + r1 * (ll)i) % mm;
    m = mm;
  }
  return r;
}

vector<pair<int, int>> factorize(int m) {
  vector<pair<int, int>> ret;
  for (int x = 2; x * x <= m; ++x)
    if (m % x == 0) {
      int c = 0;
      while (m % x == 0) {
        m /= x;
        ++c;
      }
      ret.emplace_back(x, c);
    }
  if (m != 1)
    ret.emplace_back(m, 1);
  return ret;
};

int mpow(int x, ll k, int m) {
  int ret = 1;
  while (k) {
    if (k & 1)
      ret = ret * (ll)x % m;
    x = x * (ll)x % m;
    k >>= 1;
  }
  return ret;
}

int binom(ll n, ll m, int p, int k) {
  int pk = 1;
  for (int rep = 0; rep < k; ++rep)
    pk *= p;
  vector<ll> coe(pk);
  function<void(ll, int)> apply = [&](ll n, int sign) {
    while (n) {
      for (int i = 1; i < pk && i <= n; ++i)
        if (i % p)
          coe[i] += sign * ((n - i) / pk + 1);
      coe[0] += sign * (n /= p);
    }
  };
  apply(n, 1);
  apply(m, -1);
  apply(n - m, -1);
  int ret = mpow(p, coe[0], pk);
  for (int i = 1; i < pk; ++i)
    if (coe[i] >= 0)
      ret = ret * (ll)mpow(i, coe[i], pk) % pk;
    else
      ret = ret * (ll)mpow(inv(i, pk), -coe[i], pk) % pk;
  return ret;
}
