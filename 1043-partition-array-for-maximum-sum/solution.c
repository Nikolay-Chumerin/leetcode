/*
 * @lc app=leetcode id=1043 lang=c
 *
 * [1043] Partition Array for Maximum Sum
 *
 * https://leetcode.com/problems/partition-array-for-maximum-sum/description/
 *
 * algorithms
 * Medium (72.44%)
 * Likes:    4367
 * Dislikes: 358
 * Total Accepted:    150.5K
 * Total Submissions: 197.9K
 * Testcase Example:  '[1,15,7,9,2,5,10]\n3'
 *
 * Given an integer array arr, partition the array into (contiguous) subarrays
 * of length at most k. After partitioning, each subarray has their values
 * changed to become the maximum value of that subarray.
 *
 * Return the largest sum of the given array after partitioning. Test cases are
 * generated so that the answer fits in a 32-bit integer.
 *
 *
 * Example 1:
 *
 *
 * Input: arr = [1,15,7,9,2,5,10], k = 3
 * Output: 84
 * Explanation: arr becomes [15,15,15,9,10,10,10]
 *
 *
 * Example 2:
 *
 *
 * Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
 * Output: 83
 *
 *
 * Example 3:
 *
 *
 * Input: arr = [1], k = 1
 * Output: 1
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= arr.length <= 500
 * 0 <= arr[i] <= 10^9
 * 1 <= k <= arr.length
 *
 *
 */

// @lc code=start
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize(-flto, -ffast - math, -march = native, -mtune = native)

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX_N (500)
int maxSumAfterPartitioning(int* a, const int n, const int k) {
  int s[MAX_N + 1] = {[0] = 0};
  s[1] = a[0];
  for (int i = 1; i < n; ++i) {
    int max_a = 0;
    int max_s = 0;
    const int max_j = MIN(k, i + 1);
    for (int j = 0; j < max_j; ++j) {
      max_a = MAX(max_a, a[i - j]);
      max_s = MAX(max_s, max_a * (j + 1) + s[i - j]);
    }
    s[i + 1] = max_s;
  }  // i-loop
  return s[n];
}
/*
#define MAX_K (500)
int maxSumAfterPartitioning_v2(int* a, const int n, const int max_k) {
  int d[2][MAX_N + 1];
  memset(d, 0, sizeof(d));

  d[0][n - 1] = d[1][n - 1] = a[n - 1];
  int curr = 0, prev = 1;
  for (int i = n - 2; i >= 0; --i)
    d[curr][i] = a[i] + d[curr][i + 1];

  for (int k = 2; k <= max_k; ++k) {
    printf("k=%d\n", k);
    curr ^= 1;
    prev = 1 - curr;
    for (int i = n - 2; i >= 0; --i) {
      int c = a[i] + d[curr][i + 1];
      c = MAX(c, d[prev][i]);
      int max_a = a[i];
      int cc = max_a + d[curr][i + 1];
      const int max_j = MIN(k, n - i);
      int j = 1;
      for (; j < max_j; ++j) {
        max_a = MAX(max_a, a[i + j]);
        const int ccc = max_a * (j + 1) + d[curr][i + j + 1];
        cc = MAX(cc, ccc);
      }
      d[curr][i] = MAX(c, cc);
    }  // i-loop
  }  // k-loop
  return d[curr][0];
}
*/// @lc code=end
