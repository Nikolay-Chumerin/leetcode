/*
 * @lc app=leetcode id=1155 lang=c
 *
 * [1155] Number of Dice Rolls With Target Sum
 *
 * https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/description/
 *
 * algorithms
 * Medium (54.67%)
 * Likes:    4947
 * Dislikes: 164
 * Total Accepted:    276K
 * Total Submissions: 454.9K
 * Testcase Example:  '1\n6\n3'
 *
 * You have n dice, and each dice has k faces numbered from 1 to k.
 * 
 * Given three integers n, k, and target, return the number of possible ways
 * (out of the k^n total ways) to roll the dice, so the sum of the face-up
 * numbers equals target. Since the answer may be too large, return it modulo
 * 10^9 + 7.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 1, k = 6, target = 3
 * Output: 1
 * Explanation: You throw one die with 6 faces.
 * There is only one way to get a sum of 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 2, k = 6, target = 7
 * Output: 6
 * Explanation: You throw two dice, each with 6 faces.
 * There are 6 ways to get a sum of 7: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 30, k = 30, target = 500
 * Output: 222616187
 * Explanation: The answer must be returned modulo 10^9 + 7.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n, k <= 30
 * 1 <= target <= 1000
 * 
 * 
 */

// @lc code=start
#define MOD (1000000007)
int cache[31][1001] = {-1}; 
int nrolls(const int n, const int k, const int target) {
  if ((n <= 0) || (n > target) || (n * k < target)) {
    return 0;
  }
  if (n == 1 && target <= k && target > 0) return 1;
  int ans = cache[n][target];
  if (ans >= 0) return ans;
  ans = 0;

  for (int i = 1; i <= k && target >= i; ++i) {
    ans += nrolls(n - 1, k, target - i);
    ans %= MOD;
  }
  cache[n][target] = ans;
  return ans;
}

int numRollsToTarget(const int n, const int k, const int target) {
  memset(cache, -1, sizeof(cache));
  return nrolls(n, k, target);
}
// @lc code=end