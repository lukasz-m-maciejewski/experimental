struct S {
  int a;
  double b;
};

namespace my {
inline int extern x = 5;
constexpr int y = 10;
inline S ncn_s{1, 2.0};
inline S const cn_s{2, 3.0};
}  // namespace my

inline S extern ncg_s{1, 2.0};
inline S extern const cg_s{2, 3.0};

int first_get_x() { return my::x; }

void const* first_get_y() { return static_cast<void const*>(&my::y); }
