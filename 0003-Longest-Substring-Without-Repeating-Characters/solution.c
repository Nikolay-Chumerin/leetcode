int lengthOfLongestSubstring(char *s) {
  int set[256];
  memset(set, 0, sizeof(set));
  int right = 0;
  int left = 0;
  int max_len = 0;
  while (s[right]) {
    const int *right_char_in_set_ptr = &set[s[right]];
    while (*right_char_in_set_ptr) {
      set[s[left++]] = 0;
    } // left-loop
    set[s[right++]] = 1;

    const int len = right - left;
    if (max_len < len) {
      max_len = len;
    }
  } // right-loop
  return max_len;
}