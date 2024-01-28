/*
 * @lc app=leetcode id=629 lang=c
 *
 * [629] K Inverse Pairs Array
 *
 * https://leetcode.com/problems/k-inverse-pairs-array/description/
 *
 * algorithms
 * Hard (50.24%)
 * Likes:    2553
 * Dislikes: 306
 * Total Accepted:    118.7K
 * Total Submissions: 236.3K
 * Testcase Example:  '3\n0'
 *
 * For an integer array nums, an inverse pair is a pair of integers [i, j]
 * where 0 <= i < j < nums.length and nums[i] > nums[j].
 *
 * Given two integers n and k, return the number of different arrays consist of
 * numbers from 1 to n such that there are exactly k inverse pairs. Since the
 * answer can be huge, return it modulo 10^9 + 7.
 *
 *
 * Example 1:
 *
 *
 * Input: n = 3, k = 0
 * Output: 1
 * Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3
 * has exactly 0 inverse pairs.
 *  
 *
 * Example 2:
 *
 *
 * Input: n = 3, k = 1
 * Output: 2
 * Explanation: The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= n <= 1000
 * 0 <= k <= 1000
 *
 *
 */

// @lc code=start
#define MOD 1000000007
#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
int kInversePairs(const int n, const int k) {
  // T(1, 0) = 1,
  // T(n, k) = 0 for n < 0, k < 0 or k > n*(n-1)/2.
  // T(n, k) = Sum_{j=0..n-1} T(n-1, k-j)

  // n\k| 0  1   2    3    4     5     6     7     8      9     10
  // ---+--------------------------------------------------------------
  //  1 | 1;
  //  2 | 1, 1;
  //  3 | 1, 2,  2,   1;
  //  4 | 1, 3,  5,   6,   5,    3,    1;
  //  5 | 1, 4,  9,  15,  20,   22,   20,   15,    9,     4,     1;
  //  6 | 1, 5, 14,  29,  49,   71,   90,  101,  101,    90,    71, ...
  //  7 | 1, 6, 20,  49,  98,  169,  259,  359,  455,   531,   573, ...
  //  8 | 1, 7, 27,  76, 174,  343,  602,  961, 1415,  1940,  2493, ...
  //  9 | 1, 8, 35, 111, 285,  628, 1230, 2191, 3606,  5545,  8031, ...
  // 10 | 1, 9, 44, 155, 440, 1068, 2298, 4489, 8095, 13640, 21670, ...

  const int n2 = n * (n - 1) / 2;
  if ((n < 0) || (k < 0) || (k > n2)) return 0;
  if ((n < 3) || (k == 0) || (k == n2)) return 1;
  if ((k == 2) || (k == n2 - 2)) return n2 - 1;
  if ((k == 1) || (k == n2 - 1)) return n - 1;
  int t[2][k + 1];
  memset(t, 0, sizeof(t));
  int curr = 1;
  int prev = 0;
  t[prev][0] = t[prev][1] = 1;
  for (int ni = 3; ni <= n; ++ni) {
    const int n2i = ni * (ni - 1) / 2;
    const int n22i = (n2i + 1) / 2;
    const int max_ki = MIN(k, n2i);
    for (int ki = 0; ki <= max_ki; ++ki) {
      if (ki <= n22i) {
        long sum = 0;
        for (int j = MAX(0, ki - ni + 1); j <= ki; ++j) {
          sum += t[prev][j];
        }
        t[curr][ki] = (int)(sum % MOD);
      } else {
        t[curr][ki] = t[curr][n2i - ki];
      }
    }  // ki-loop
    curr ^= 1;
    prev ^= 1;
  }

  return t[prev][k];
}

// Recursive vrsion
int kInversePairs_recursive(const int n, const int k) {
  // T(1, 0) = 1,
  // T(n, k) = 0 for n < 0, k < 0 or k > n*(n-1)/2.
  // T(n, k) = Sum_{j=0..n-1} T(n-1, k-j),
  if ((1 == n) && (0 == k)) return 1;
  if ((n < 0) || (k < 0) || (k > n * (n - 1) / 2)) return 0;
  return (kInversePairs(n, k - 1) + kInversePairs(n - 1, k) -
          kInversePairs(n - 1, k - n)) %
         MOD;
} 
// @lc code=end
