vector<Vec> hull(const vector<Vec>& seq, int sign) {
  vector<Vec> ret;
  int n = seq.size(), top = 0;
  for (int i = 0; i < n; ++i) {
    if (!ret.empty() && seq[i].x == ret.back().x)
      if ((seq[i].y - ret[top - 1].y) * sign >= 0) {
        ret.pop_back();
        --top;
      } else
        continue;
    while (top > 1 && (ret[top - 1] - ret[top - 2]) * (seq[i] - ret[top - 1]) * sign >= 0) {
      ret.pop_back();
      --top;
    }
    ret.push_back(seq[i]);
    ++top;
  }
  return ret;
}
