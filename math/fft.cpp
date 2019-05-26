typedef complex<double> Cp;

const int L = 18;
const double PI = acos(-1.0);

void fft(Cp* a, int lgn, int d) {
  static int brev[1 << L];
  int n = 1 << lgn;
  for (int i = 1; i < n; ++i)
    brev[i] = (brev[i >> 1] >> 1) | ((i & 1) << ((lgn - 1)));
  for (int i = 0; i < n; ++i)
    if (i < brev[i])
      swap(a[i], a[brev[i]]);
  for (int i = 0; i < lgn; ++i) {
    int t = 1 << i;
    Cp omega(cos(PI / t), sin(PI / t) * d);
    for (int j = 0; j < n; j += t << 1) {
      Cp w = 1;
      for (int k = 0; k < t; ++k) {
        Cp a0 = a[j + k], a1 = a[j + k + t];
        a[j + k] = a0 + w * a1;
        a[j + k + t] = a0 - w * a1;
        w *= omega;
      }
    }
  }
  if (d == -1)
    for (int i = 0; i < n; ++i)
      a[i] /= n;
}
