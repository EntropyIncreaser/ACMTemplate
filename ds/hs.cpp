typedef long long ll;

const ll INF = 1LL << 60;

struct Node {
  int l, r;
  ll v, hv, lz, hlz;
  union {
    struct { Node *ls, *rs; };
    Node* c[2];
  };

  ll get() const { return v + lz; }

  void upd() {
    v = max(ls->get(), rs->get());
    hv = max(ls->hv, rs->hv);
  }

  void pd() {
    v += lz;
    for (int i = 0; i < 2; ++i) {
      c[i]->hlz = max(c[i]->lz + hlz, c[i]->hlz);
      c[i]->hv = max(c[i]->hv, c[i]->v + c[i]->hlz);
      c[i]->lz += lz;
    }
    lz = 0;
    hlz = 0;
  }

  void ch(int l, int r, ll x) {
    if (this->l == l && this->r == r) {
      hlz = max(hlz, lz += x);
      hv = max(hv, v + hlz);
      return;
    }
    pd();
    if (r <= ls->r)
      ls->ch(l, r, x);
    else if (l >= rs->l)
      rs->ch(l, r, x);
    else {
      ls->ch(l, ls->r, x);
      rs->ch(rs->l, r, x);
    }
    upd();
  }

  ll qry(int l, int r) {
    if (this->l == l && this->r == r)
      return hv;
    pd();
    if (r <= ls->r)
      return ls->qry(l, r);
    if (l >= rs->l)
      return rs->qry(l, r);
    return max(ls->qry(l, ls->r), rs->qry(rs->l, r));
  }

  void ord() {
    if (l != r) {
      pd();
      for (int i = 0; i < 2; ++i)
        c[i]->ord();
      upd();
    }
  }
};

Node* build(int l, int r) {
  static Node pool[N * 4], *ptop = pool;
  Node* p = ptop++;
  p->l = l;
  p->r = r;
  p->v = p->hv = -INF * 2;
  if (l == r)
    return p;
  int mid = (l + r) >> 1;
  p->ls = build(l, mid);
  p->rs = build(mid + 1, r);
  return p;
}
