/*
 * @lc app=leetcode id=1759 lang=c
 *
 * [1759] Count Number of Homogenous Substrings
 */

// @lc code=start
#define MOD (1000000007)
int countHomogenous(char *s) { 
  uint64_t ans = 0U;
  uint64_t n = 0; /* number of repeating chars */
  char prev = 0;
  while (*s) {
    if (*s == prev) {
      ++n;
    } else {      
      ans += n * (n + 1) / 2;
      ans %= MOD;
      prev = *s;
      n = 1;
    }
    ++s;
  }
  ans += n * (n + 1) / 2;
  ans %= MOD;
  return ans;
}
// @lc code=end
