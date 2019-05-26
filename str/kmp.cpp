int nxt[N];

void kmp(char s[], int n) {
  int k = 0;
  for (int i = 2; i <= n; ++i) {
    while (k && s[i] != s[k + 1])
      k = nxt[k];
    if (s[k + 1] == s[i])
      nxt[i] = ++k;
  }
}
