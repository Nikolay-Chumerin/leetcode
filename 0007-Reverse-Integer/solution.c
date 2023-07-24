int reverse(int x) {
  int sign = 1;
  if (x < 0) {
    if (x < -2147483641)
      return 0;
    sign = -1;
    x = -x;
  }
  int y = 0;
  while (x) {
    const int d = x % 10;
    if (y > 214748364 || (y == 214748364 && d > 7))
      return 0;
    y = y * 10 + d;
    x /= 10;
  }
  return sign * y;
}