int trie[N][A], fail[N];

void buildac() {
  queue<int> q;
  q.push(1);
  fail[1] = 1;
  while (!q.empty()) {
    int p = q.front();
    q.pop();
    if (p == 1) {
      for (int i = 0; i < A; ++i)
        if (trie[p][i]) {
          fail[trie[p][i]] = p;
          q.push(trie[p][i]);
        } else
          trie[p][i] = p;
    } else {
      for (int i = 0; i < A; ++i)
        if (trie[p][i]) {
          fail[trie[p][i]] = trie[fail[p]][i];
          q.push(trie[p][i]);
        } else
          trie[p][i] = trie[fail[p]][i];
    }
  }
}
