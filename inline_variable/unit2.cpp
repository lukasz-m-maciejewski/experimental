namespace my {
inline int const x = 10;
constexpr int y = 11;
}

int second_get_x() {
  return my::x;
}

void const* second_get_y() {
  return static_cast<void const*>(&my::y);
}
