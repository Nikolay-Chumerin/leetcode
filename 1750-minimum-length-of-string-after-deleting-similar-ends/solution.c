int minimumLength(const char * const s) {
  int l = 0;
  int r = strlen(s) - 1;
  char c;
  while (l < r) {
    c = s[l];
    if (c != s[r]) return r - l + 1;
    while ((c == s[l]) && (l < r)) ++l;
    while ((c == s[r]) && (l < r)) --r;
  }
  return (r - l) + (c != s[l]);
}
