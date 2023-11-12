/*
 * @lc app=leetcode id=93 lang=c
 *
 * [93] Restore IP Addresses
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **restoreIpAddresses(char *s, int *ans_len) {
  char **ans = (char **)malloc(81 * sizeof(char *));
  *ans_len = 0;
  const int l = strlen(s);
  int byte, i;
  if (l < 4)
    return ans;
  for (int l1 = 1; l1 < 4; ++l1) {
    if (l1 > 1 && s[0] == '0')
      break;
    for (byte = 0, i = 0; i < l1; ++i)
      byte = 10 * byte + (s[i] - '0');
    if ((byte > 255) || (l1 == 2 && byte < 10) || (l1 == 3 && byte < 100))
      break;

    for (int l2 = 1; l2 < 4; ++l2) {
      if (l1 + l2 > l)
        break;
      for (byte = 0, i = l1; i < l1 + l2; ++i)
        byte = 10 * byte + (s[i] - '0');
      if ((byte > 255) || (l2 == 2 && byte < 10) || (l2 == 3 && byte < 100))
        break;
      for (int l3 = 1; l3 < 4; ++l3) {
        if (l1 + l2 + l3 >= l)
          break;
        for (byte = 0, i = l1 + l2; i < l1 + l2 + l3; ++i)
          byte = 10 * byte + (s[i] - '0');
        if ((byte > 255) || (l3 == 2 && byte < 10) || (l3 == 3 && byte < 100))
          break;

        int l4 = l - l1 - l2 - l3;
        if (l4 > 3)
          continue;
        for (byte = 0, i = l1 + l2 + l3; i < l1 + l2 + l3 + l4; ++i)
          byte = 10 * byte + (s[i] - '0');
        if ((byte > 255) || (l4 == 2 && byte < 10) || (l4 == 3 && byte < 100))
          continue;

        /* found */
        ans[*ans_len] = malloc((l + 4) * sizeof(char));
        char *dst = ans[*ans_len];
        char *src = s;
        for (i = 0; i < l1; ++i)
          *dst++ = *src++;
        *dst++ = '.';
        for (i = 0; i < l2; ++i)
          *dst++ = *src++;
        *dst++ = '.';
        for (i = 0; i < l3; ++i)
          *dst++ = *src++;
        *dst++ = '.';
        for (i = 0; i < l4; ++i)
          *dst++ = *src++;
        *dst++ = 0;
        ++(*ans_len);
      } // l3-loop
    }   // l2-loop
  }     // l1-loop
  return ans;
} // @lc code=end
