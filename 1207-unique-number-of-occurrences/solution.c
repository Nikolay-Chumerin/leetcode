/*
 * @lc app=leetcode id=1207 lang=c
 *
 * [1207] Unique Number of Occurrences
 *
 * https://leetcode.com/problems/unique-number-of-occurrences/description/
 *
 * algorithms
 * Easy (74.36%)
 * Likes:    4731
 * Dislikes: 115
 * Total Accepted:    484.5K
 * Total Submissions: 634.5K
 * Testcase Example:  '[1,2,2,1,1,3]'
 *
 * Given an array of integers arr, return true if the number of occurrences of
 * each value in the array is unique or false otherwise.
 *
 *
 * Example 1:
 *
 *
 * Input: arr = [1,2,2,1,1,3]
 * Output: true
 * Explanation: The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two
 * values have the same number of occurrences.
 *
 * Example 2:
 *
 *
 * Input: arr = [1,2]
 * Output: false
 *
 *
 * Example 3:
 *
 *
 * Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
 * Output: true
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= arr.length <= 1000
 * -1000 <= arr[i] <= 1000
 *
 *
 */

// @lc code=start
#define MAX_N (2048)
#define OFFSET (1024)
bool uniqueOccurrences(const int* a, const int n) {
  int h[MAX_N] = {0};
  int i;
  for (i = 0; i < n; ++i) ++h[a[i] + OFFSET];
  bool present[MAX_N] = {false};
  for (i = 0; i < MAX_N; ++i) {
    if (0 == h[i]) continue;
    if (present[h[i]]) return false;
    present[h[i]] = true;
  }
  return true;
}
// @lc code=end
