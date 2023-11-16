/*
 * @lc app=leetcode id=1930 lang=c
 *
 * [1930] Unique Length-3 Palindromic Subsequences
 *
 * https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/
 *
 * algorithms
 * Medium (53.98%)
 * Likes:    1209
 * Dislikes: 46
 * Total Accepted:    57.5K
 * Total Submissions: 92.8K
 * Testcase Example:  "aabca"
 *
 * Given a string s, return the number of unique palindromes of length three
 * that are a subsequence of s.
 *
 * Note that even if there are multiple ways to obtain the same subsequence, it
 * is still only counted once.
 *
 * A palindrome is a string that reads the same forwards and backwards.
 *
 * A subsequence of a string is a new string generated from the original string
 * with some characters (can be none) deleted without changing the relative
 * order of the remaining characters.
 *
 * For example, "ace" is a subsequence of "abcde".
 *
 * Example 1:
 * Input: s = "aabca"
 * Output: 3
 * Explanation: The 3 palindromic subsequences of length 3 are:
 * - "aba" (subsequence of "aabca")
 * - "aaa" (subsequence of "aabca")
 * - "aca" (subsequence of "aabca")
 *
 * Example 2:
 * Input: s = "adc"
 * Output: 0
 * Explanation: There are no palindromic subsequences of length 3 in "adc".
 *
 * Example 3:
 * Input: s = "bbcbaba"
 * Output: 4
 * Explanation: The 4 palindromic subsequences of length 3 are:
 * - "bbb" (subsequence of "bbcbaba")
 * - "bcb" (subsequence of "bbcbaba")
 * - "bab" (subsequence of "bbcbaba")
 * - "aba" (subsequence of "bbcbaba")
 *
 * Constraints:
 * 3 <= s.length <= 10^5
 * s consists of only lowercase English letters.
 *
 */

// @lc code=start
#define FIRST_CHAR 'a'
#define LAST_CHAR 'z'
#define CHARS_NUM (LAST_CHAR - FIRST_CHAR + 1)
int countPalindromicSubsequence(const char *s) {
  const int l = strlen(s);
  int i0 = -1; /* Index of char's first occurance in s */
  int i1 = 0;  /* Index of char's last occurance in s */
  int ans = 0; /* Answer */
  for (char c = FIRST_CHAR; c <= LAST_CHAR; ++c) {
    for (i0 = 0; i0 < l && c != s[i0]; ++i0)
      ;
    if (i0 >= l)
      continue;
    for (i1 = l - 1; i1 >= i0 && c != s[i1]; --i1)
      ;
    if (i0 == i1)
      continue;
    bool m[CHARS_NUM];
    memset(m, 0, sizeof(m));
    int different_chars_num = 0;
    for (int i = i0 + 1; i < i1; ++i) {
      const int ci = s[i] - FIRST_CHAR;
      if (!m[ci]) {
        m[ci] = true;
        if (++different_chars_num >= CHARS_NUM)
          break;
      } /* if */
    }   /* scan of string s between i0 and i1 */
    ans += different_chars_num;
  } /* loop over all chars */
  return ans;
}
/********************************************************/
// #define CHARS_NUM (26)
// #define CHAR2IDX(c) (c - 'a')
// #define FILL(arr, val) memset(arr, val, sizeof(arr))

// int countPalindromicSubsequence(const char *s) {
//   const int l = strlen(s);
//   int i0[CHARS_NUM]; /* indices of char first occurance in s */
//   int i1[CHARS_NUM]; /* indices of char last occurance in s */
//   FILL(i0, -1);
//   FILL(i1, 0);

//   /* fill out i0[] and i1[] arrays */
//   for (int i = 0; i < l; ++i) {
//     const int ci = CHAR2IDX(s[i]);
//     if (i0[ci] < 0) {
//       i0[ci] = i;
//     } else if (i > i1[ci]) {
//       i1[ci] = i;
//     }
//   } /* for-loop */

//   char om[CHARS_NUM][CHARS_NUM];
//   FILL(om, 0);
//   for (int i = 0; i < l; ++i) {
//     const int ci = CHAR2IDX(s[i]);
//     for (int cj = 0; cj < CHARS_NUM; ++cj) {
//       if ((i0[cj] < i) && (i < i1[cj])) {
//         om[cj][ci] = 1;
//       }
//     } /* cj-loop over 26 chars */
//   }   /* s-scan for-loop */

//   int ans = 0; /* Answer */
//   for (int i = 0; i < CHARS_NUM; ++i)
//     for (int j = 0; j < CHARS_NUM; ++j)
//       ans += om[i][j];

//   return ans;
// }

// @lc code=end
