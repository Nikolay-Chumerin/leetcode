
#define APPEND_CHAR_IF_ITS_OK(idx, res_itr, len, s, last_idx) \
  if (idx >= 0 && idx < len && idx != last_idx) { \
      *res_itr++ = s[idx];                        \
      last_idx = idx;                             \
  }


char * convert(char * s, int rows_num) {
  const int len = strlen(s);
  char* res = (char*) malloc(len + 1);
  if (rows_num <= 1 || rows_num >= len) {
    strcpy(res, s);
    return res;
  }

  char* res_itr = res;
  const int pattern_len = (rows_num - 1) * 2;  // number of chars in one zigzag repeating pattern
  const int patterns_num = (len + pattern_len -1) / pattern_len;
  int idx, last_idx;
  for (int row_idx = 0; row_idx < rows_num; ++row_idx) {
      last_idx = -len;
      for (int pattern_idx = 0; pattern_idx <= patterns_num; ++pattern_idx) {
          idx = pattern_len * pattern_idx - row_idx;  // left candidate
          APPEND_CHAR_IF_ITS_OK(idx, res_itr, len, s, last_idx);
          idx += row_idx + row_idx;  // right candidate
          APPEND_CHAR_IF_ITS_OK(idx, res_itr, len, s, last_idx);
      }  // loop over zigzag repeating patterns
      *res_itr = 0;
  }  // loop over rows in "zigzag"
  return res;
}
