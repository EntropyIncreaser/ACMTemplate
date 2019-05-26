typedef __int128 i128;

i128 n;

i128 mul(i128 x, i128 y) {
  i128 ret = 0;
  while (x) {
    if (x & 1)
      ret = (ret + y) % n;
    y = (y + y) % n;
    x >>= 1;
  }
  return ret;
}

i128 gcd(i128 a, i128 b) { return b ? gcd(b, a % b) : a; }

i128 g(i128 x) { return (mul(x, x) + 1) % n; }

pair<i128, i128> fact2(i128 n) {
  i128 x = 2, y = 2;
  while (true) {
    x = g(x);
    y = g(g(y));
    i128 d = x - y;
    if (d < 0)
      d = -d;
    d = gcd(d, n);
    if (d != 1 && d != n) {
      i128 p = d, q = n / d;
      if (p > q)
        swap(p, q);
      return make_pair(p, q);
    }
  }
};
