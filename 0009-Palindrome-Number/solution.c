bool isPalindrome(int x) {
  if (x < 0) return false;
  unsigned long long a = x, b = 0;
  while (x) {
    b *= 10;
    b += x % 10;
    x /= 10;
  }
  return a == b;
}