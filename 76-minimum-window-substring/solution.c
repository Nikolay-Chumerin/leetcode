/*
 * @lc app=leetcode id=76 lang=c
 *
 * [76] Minimum Window Substring
 *
 * https://leetcode.com/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (41.73%)
 * Likes:    17297
 * Dislikes: 702
 * Total Accepted:    1.3M
 * Total Submissions: 3M
 * Testcase Example:  '"ADOBECODEBANC"\n"ABC"'
 *
 * Given two strings s and t of lengths m and n respectively, return the
 * minimum window substring of s such that every character in t (including
 * duplicates) is included in the window. If there is no such substring, return
 * the empty string "".
 *
 * The testcases will be generated such that the answer is unique.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 * Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C'
 * from string t.
 *
 *
 * Example 2:
 *
 *
 * Input: s = "a", t = "a"
 * Output: "a"
 * Explanation: The entire string s is the minimum window.
 *
 *
 * Example 3:
 *
 *
 * Input: s = "a", t = "aa"
 * Output: ""
 * Explanation: Both 'a's from t must be included in the window.
 * Since the largest window of s only has one 'a', return empty string.
 *
 *
 *
 * Constraints:
 *
 *
 * m == s.length
 * n == t.length
 * 1 <= m, n <= 10^5
 * s and t consist of uppercase and lowercase English letters.
 *
 *
 *
 * Follow up: Could you find an algorithm that runs in O(m + n) time?
 *
 */

// @lc code=start
/* Proper sliding window and two pointers solution */
#define MAX_CHAR 'z'
typedef int hist_t[MAX_CHAR + 1];  // count of each letter (in some string)

char* minWindow(char* s, char* t) {
  const int s_len = strlen(s);
  const int t_len = strlen(t);
  int best_start_idx = 0;
  int best_len = s_len + 1;
  if (s_len < t_len) goto exit;

  // Prepare histogram for the target word (ht)
  hist_t ht;
  memset(ht, 0, sizeof(hist_t));
  for (int i = 0; i < t_len; ++i) ++ht[t[i]];

  int start_idx = 0;
  int end_idx = 0;
  int missed_chars_num = t_len;

  while (end_idx < s_len) {
    missed_chars_num -= (--ht[s[end_idx++]] >= 0);

    while (!missed_chars_num) {
      const int curr_len = end_idx - start_idx;
      if (curr_len < best_len) {
        best_start_idx = start_idx;
        best_len = curr_len;
      }
      missed_chars_num += (++ht[s[start_idx++]] == 1);
    }  // loop of shrinking window
  }    // main loop
exit:
  s += best_start_idx;
  s[(best_start_idx + best_len <= s_len) ? best_len : 0] = 0;
  return s;
}

/* Bruteforce solution: barely passes time requirenments...
#define MIN_CHAR 'A'
#define MAX_CHAR 'z'
// #define DEBUG

typedef int hist_t[MAX_CHAR + 1];

#ifdef DEBUG
#define hist_print(a) \
  {}
#else
#define puts(a) \
  {}
#define printf(fmt, ...) \
  {}
void hist_print(const hist_t* h) {
  printf("[ ");
  for (char c = MIN_CHAR; c <= MAX_CHAR; ++c) {
    if ((*h)[c]) printf("%c=%d ", c, (*h)[c]);
  }
  printf("]\n");
}
#endif  // DEBUG

bool hw_contains_ht(const hist_t* hw, const hist_t* ht) {
  for (char c = MIN_CHAR; c <= MAX_CHAR; ++c)
    if (*(ht + c) > *(hw + c)) return false;
  return true;
}

int count_missing_chars_num(const hist_t* hw, const hist_t* ht) {
  int ans = 0;
  for (char c = MIN_CHAR; c <= MAX_CHAR; ++c) {
    if (!(*ht)[c]) continue;
    const int diff = (*ht)[c] - (*hw)[c];
    ans += diff > 0 ? diff : 0;
  }
  printf("hw=");
  hist_print(hw);
  printf("ht=");
  hist_print(ht);
  printf("hw misses %d char(s) from ht\n", ans);
  return ans;
}

char* minWindow(char* s, char* t) {
  puts("----------------------");
  const int ls = strlen(s);
  const int lt = strlen(t);
  printf("ls=%d lt=%d\n", ls, lt);
  int best_idx = 0;
  int best_len = 0;
  if (ls < lt) goto exit;
  best_idx = -1;
  best_len = ls + 1;

  // Prepare histogram for the target word (ht)
  hist_t ht;  // histogram for the target word
  memset(ht, 0, sizeof(hist_t));
  for (int i = 0; i < lt; ++i) ++ht[t[i]];
  printf("ht=");
  hist_print(&ht);

  // Prepare fixed-size sliding window histogram (hs)
  hist_t hs;  // histogram for the sliding window (of fixed len lt)
  memset(hs, 0, sizeof(hist_t));  // clear
  for (int i = 0; i < lt; ++i) ++hs[s[i]];
  printf("hs=");
  hist_print(&hs);

  hist_t hw;  // histogram for the sliding window (of variable len lt...)

  for (int i = 0; i <= (ls - lt); ++i) {
    if ((i) && (s[i - 1] == s[i]) && (s[i] == s[i + lt]) &&
        (s[i + lt - 1] == s[i + lt])) {
      printf("Skipping i=%d\n", i);
      continue;
    }
    memcpy(hw, hs, sizeof(hs));
    int missing_chars_num = count_missing_chars_num(&hw, &ht);
    printf("i=%d missing_chars_num=%d\n", i, missing_chars_num);
    if (!missing_chars_num) {
      best_idx = i;
      best_len = lt;
      printf("found: best_idx=%d best_len=%d\n", best_idx, best_len);
      goto exit;
    }

    for (int l = lt + 1; (l <= (ls - i)) && (l < best_len); ++l) {
      const char ch = s[i + l - 1];  // new char to be added to the sliding win
      printf("i=%d l=%d ch=s[%d]=%c\n", i, l, i + l - 1, ch);
      if (ht[ch] <= hw[ch])
        continue;  // skip chars, which we have enough or aren't in t
      printf("ht[%c]=%d > %d=hw[%c] missing_chars_num=%d", ch, ht[ch], hw[ch],
             ch, missing_chars_num);
      ++hw[ch];
      --missing_chars_num;
      printf("->%d hw[%c]=%d->%d\n", missing_chars_num, ch, hw[ch] - 1, hw[ch]);
      if (missing_chars_num <= 0) {
        best_idx = i;
        best_len = l;
        printf("found: best_idx=%d best_len=%d\n", best_idx, best_len);
        break;
      }  // if (missing_chars_num <= 0)
      printf("i=%d l=%d hw=", i, l);
      hist_print(&hw);
    }  // l-loop (length)

    // updated histogram (hs) of the slided (fixed-len) window
    --hs[s[i]];
    ++hs[s[i + lt]];
    printf("--hs[s[%d]](hs[%c])<-%d\n", i, s[i], hs[s[i]]);
    printf("++hs[s[i+lt]=hs[s[%d]](hs[%c])<-%d\n", i + lt, s[i + lt],
           hs[s[i + lt]]);

    printf("i->%d l=%d\nhs=", i + 1, lt);
    hist_print(&hs);
    printf("ht=");
    hist_print(&ht);
    puts("-[ end of i-loop iterations]-----");
  }  // i-loop (index)

  if (best_idx < 0) best_idx = best_len = 0;
exit:
  s[best_idx + best_len] = 0;
  // printf("best_idx=%d best_len=%d ans='%s'\n", best_idx, best_len, s +
  // best_idx);
  return s + best_idx;
}
*/
// @lc code=end
