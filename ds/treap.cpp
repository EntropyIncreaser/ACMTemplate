struct Tmp;

mt19937 gnr(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
  Tmp k;
  int r, sz, cnt;
  Node *ls, *rs;
};

Node pool[M + N], *ptop;

Node* create(const Tmp& k) {
  Node* p = ptop++;
  p->k = k;
  p->r = gnr();
  p->sz = p->cnt = 1;
  p->ls = p->rs = NULL;
  return p;
}

int gc(Node* p) { return p ? p->cnt : 0; }

void upd(Node* p) { p->cnt = p->sz + gc(p->ls) + gc(p->rs); }

Node* zip(Node* p, Node* q) {
  if (!p) return q;
  if (!q) return p;
  if (p->r > q->r) {
    p->rs = zip(p->rs, q);
    upd(p);
    return p;
  }
  q->ls = zip(p, q->ls);
  upd(q);
  return q;
}

Node* insert(Node* p, Node* o) {
  if (p == NULL)
    return o;
  if (p->k == o->k) {
    ++p->sz;
    ++p->cnt;
    return p;
  }
  if (o->k < p->k) {
    Node* t = p->ls;
    p->ls = NULL;
    upd(p);
    return zip(insert(t, o), p);
  }
  Node* t = p->rs;
  p->rs = NULL;
  upd(p);
  return zip(p, insert(t, o));
}

Node* erase(Node* p, const Tmp& k) {
  if (p->k == k) {
    --p->cnt;
    if (--p->sz == 0)
      return zip(p->ls, p->rs);
    return p;
  }
  if (k < p->k) {
    Node* t = p->ls;
    p->ls = NULL;
    upd(p);
    return zip(erase(t, k), p);
  }
  Node* t = p->rs;
  p->rs = NULL;
  upd(p);
  return zip(p, erase(t, k));
}

struct Treap {
  Node* root;

  Treap() : root() {
    ptop = pool;
  }

  void insert(const Tmp& k) {
    root = ::insert(root, create(k));
  }

  void erase(const Tmp& k) {
    root = ::erase(root, k);
  }

  int rank(const Tmp& k) {
    Node* o = root;
    int ret = 0;
    while (o) {
      if (k < o->k)
        o = o->ls;
      else if (k == o->k)
        return ret + gc(o->ls);
      else {
        ret += gc(o->ls) + o->sz;
        o = o->rs;
      }
    }
    return ret;
  }
};
