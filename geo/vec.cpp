#define Num double

struct Vec {
  Num x, y;

  Vec() {}

  Vec(Num x, Num y) : x(x), y(y) {}

  Num len() const {
    return sqrt(x * x + y * y);
  }

  Vec rot90() const {
    return Vec(-y, x);
  }

  Vec rot90(const Vec &v) const {
    return (*this - v).rot90() + v;
  }

  Vec operator-() const {
    return Vec(-x, -y);
  }

  Vec operator+(const Vec &v) const {
    return Vec(x + v.x, y + v.y);
  }

  Vec operator-(const Vec &v) const {
    return Vec(x - v.x, y - v.y);
  }

  Vec operator+=(const Vec &v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  Vec operator-=(const Vec &v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  Vec operator*(Num a) const {
    return Vec(x * a, y * a);
  }

  Vec operator/(Num a) const {
    return Vec(x / a, y / a);
  }

  Num operator^(const Vec &v) const {
    return x * v.x + y * v.y;
  }

  Num operator*(const Vec &v) const {
    return x * v.y - y * v.x;
  }

  friend Vec operator*(Num a, const Vec &v) {
    return Vec(a * v.x, a * v.y);
  }

  Num angle(Vec u, Vec v) const {
    u -= *this;
    v -= *this;
    return acos((u / u.len()) ^ (v / v.len()));
  }

  friend Vec intersect(const Vec &p1, const Vec &p2, const Vec &q1, const Vec &q2) {
    Num a1 = (q1 - p1) * (q2 - q1), a2 = (p2 - q1) * (q2 - p2);
    return (p2 - p1) * a1 / (a1 + a2) + p1;
  }
};
