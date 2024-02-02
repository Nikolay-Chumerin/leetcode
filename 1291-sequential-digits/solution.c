/*
 * @lc app=leetcode id=1291 lang=c
 *
 * [1291] Sequential Digits
 *
 * https://leetcode.com/problems/sequential-digits/description/
 *
 * algorithms
 * Medium (61.33%)
 * Likes:    2369
 * Dislikes: 146
 * Total Accepted:    138.5K
 * Total Submissions: 217.6K
 * Testcase Example:  '100\n300'
 *
 * An integer has sequential digits if and only if each digit in the number is
 * one more than the previous digit.
 *
 * Return a sorted list of all the integers in the range [low, high] inclusive
 * that have sequential digits.
 *
 *
 * Example 1:
 * Input: low = 100, high = 300
 * Output: [123,234]
 * Example 2:
 * Input: low = 1000, high = 13000
 * Output: [1234,2345,3456,4567,5678,6789,12345]
 *
 *
 * Constraints:
 *
 *
 * 10 <= low <= high <= 10^9
 *
 *
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define N (36)  //  (1 + 8) * 8 / 2
const int n[N] = {
    12,       23,       34,      45,     56,    67,   78,  89,  // 8 x 2
    123,      234,      345,     456,    567,   678,  789,      // 7 x 3
    1234,     2345,     3456,    4567,   5678,  6789,           // 6 x 4
    12345,    23456,    34567,   45678,  56789,                 // 5 x 5
    123456,   234567,   345678,  456789,                        // 4 x 6
    1234567,  2345678,  3456789,                                // 3 x 7
    12345678, 23456789,                                         // 2 x 8
    123456789                                                   // 1 x 9
};

int* sequentialDigits(const int low, const int high, int* out_n) {
  int* ans = malloc(N * sizeof(int));
  *out_n = 0;
  for (int i = 0; i < N; ++i) {
    if (n[i] < low) continue;
    if (n[i] > high) break;
    ans[(*out_n)++] = n[i];
  }
  return ans;
}
// @lc code=end
