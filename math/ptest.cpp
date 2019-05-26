typedef long long ll;

int primes[] = { 2, 3, 5, 7, 11, 13, 19, 23, 29, 31 };

bool _test(ll x, ll p) {
  ll k = x - 1;
  int l = __builtin_ctzll(k);
  k >>= l;
  ll tmp = 1;
  while (k) {
    if (k & 1)
      tmp = tmp * (__int128)p % x;
    p = p * (__int128)p % x;
    k >>= 1;
  }
  while (l--) {
    ll res = tmp * (__int128)tmp % x;
    if (res == 1 && tmp != 1 && tmp != x - 1)
      return false;
    tmp = res;
  }
  return tmp == 1;
}

bool ptest(ll x) {
  if (x <= 1) return false;
  for (int i = 0; i < 10; ++i)
    if (x == primes[i])
      return true;
    else if (!_test(x, primes[i]))
      return false;
  return true;
}
