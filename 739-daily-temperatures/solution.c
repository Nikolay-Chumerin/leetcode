/*
 * @lc app=leetcode id=739 lang=c
 *
 * [739] Daily Temperatures
 *
 * https://leetcode.com/problems/daily-temperatures/description/
 *
 * algorithms
 * Medium (65.90%)
 * Likes:    12725
 * Dislikes: 296
 * Total Accepted:    875.9K
 * Total Submissions: 1.3M
 * Testcase Example:  '[73,74,75,71,69,72,76,73]'
 *
 * Given an array of integers temperatures represents the daily temperatures,
 * return an array answer such that answer[i] is the number of days you have to
 * wait after the i^th day to get a warmer temperature. If there is no future
 * day for which this is possible, keep answer[i] == 0 instead.
 * 
 * 
 * Example 1:
 * Input: temperatures = [73,74,75,71,69,72,76,73]
 * Output: [1,1,4,2,1,1,0,0]
 * Example 2:
 * Input: temperatures = [30,40,50,60]
 * Output: [1,1,1,0]
 * Example 3:
 * Input: temperatures = [30,60,90]
 * Output: [1,1,0]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= temperatures.length <= 10^5
 * 30 <= temperatures[i] <= 100
 * 
 * 
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* t, const int n, int* out_n) {
  *out_n = n;
  int *a = (int*) calloc(n, sizeof(int));
  int j;
  for (int i = n - 2; i >= 0; --i) {
    const int ti = t[i];
    j = 1;
    while ((i + j < n) && (ti > t[i + j]))
      j += a[i + j] ?: 1;
    if (i + j >= n) continue;
    if (ti == t[i + j]) {
      a[i] = a[i + j] ? a[i + j] + j : 0;
      continue;
    }
    a[i] = j;
  }  // i-loop
  return a;
}

/*
int* dailyTemperatures_(int* t, const int n, int* out_n) {
  *out_n = n;
  int *ans = (int*) calloc(n, sizeof(int));
  int j = 1;
  while ((j < n) && (t[0] >= t[j])) ++j;
  ans[0] = (j < n) ? j : 0;

  for (int i = 1; i < n - 1; ++i) {
    const int ti = t[i];
    const int ai1 = ans[i - 1];
    if (t[i - 1] <= ti) {
      if (ai1 == 0) continue;
      if (ti < t[i - 1 + ai1]) {
        ans[i] = ai1 - 1;
        continue;
      } else {
        j = ai1;
      }
    } else {
      j = 1;
    }
    const int ni = n - i;
    while ((j < ni) && (ti >= t[i + j])) ++j;
    ans[i] = (j < ni) ? j : 0;
  }  // i-loop
  return ans;
}

*/// @lc code=end

