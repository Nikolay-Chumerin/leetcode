/*
 * @lc app=leetcode id=1611 lang=c
 *
 * [1611] Minimum One Bit Operations to Make Integers Zero
 *
 * https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/description/
 *
 * algorithms
 * Hard (63.55%)
 * Likes:    722
 * Dislikes: 794
 * Total Accepted:    39.8K
 * Total Submissions: 54.3K
 * Testcase Example:  '3'
 *
 * Given an integer n, you must transform it into 0 using the following
 * operations any number of times:
 * 
 * 
 * Change the rightmost (0^th) bit in the binary representation of n.
 * Change the i^th bit in the binary representation of n if the (i-1)^th bit is
 * set to 1 and the (i-2)^th through 0^th bits are set to 0.
 * 
 * 
 * Return the minimum number of operations to transform n into 0.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3
 * Output: 2
 * Explanation: The binary representation of 3 is "11".
 * "11" -> "01" with the 2^nd operation since the 0^th bit is 1.
 * "01" -> "00" with the 1^st operation.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 6
 * Output: 4
 * Explanation: The binary representation of 6 is "110".
 * "110" -> "010" with the 2^nd operation since the 1^st bit is 1 and 0^th
 * through 0^th bits are 0.
 * "010" -> "011" with the 1^st operation.
 * "011" -> "001" with the 2^nd operation since the 0^th bit is 1.
 * "001" -> "000" with the 1^st operation.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= n <= 10^9
 * 
 * 
 */

// @lc code=start
int minimumOneBitOperations(int n) {
  n ^= n >> 16;
  n ^= n >> 8;
  n ^= n >> 4;
  n ^= n >> 2;
  n ^= n >> 1;
  return n;
}

// int minimumOneBitOperations(const int n) {
//   if (n < 2) return n;
//   const int bit_mask = (1 << (31 - __builtin_clz(n)));
//   return 2*bit_mask - 1 - minimumOneBitOperations(n ^ bit_mask);
// }

// @lc code=end

