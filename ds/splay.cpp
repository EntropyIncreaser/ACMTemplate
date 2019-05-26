struct Node {
  Node *prt;
  union {
    struct { Node *ls, *rs; };
    Node* ch[2];
  };

  Node() {}

  bool rel() const { return this == prt->rs; }

  void upd() {
  }

  void rot() {
    bool f = rel();
    Node* p = prt;
    prt = p->prt;
    if (prt)
      prt->ch[p->rel()] = this;
    p->ch[f] = ch[!f];
    if (ch[!f])
      ch[!f]->prt = p;
    ch[!f] = p;
    p->prt = this;
    p->upd();
    upd();
  }

  void spl(Node* goal = NULL) {
    while (prt != goal) {
      if (prt->prt == goal)
        return rot();
      if (rel() == prt->rel()) {
        prt->rot();
        rot();
      } else {
        rot();
        rot();
      }
    }
  }
};
