/*
 * @lc app=leetcode id=446 lang=c
 *
 * [446] Arithmetic Slices II - Subsequence
 *
 * https://leetcode.com/problems/arithmetic-slices-ii-subsequence/description/
 *
 * algorithms
 * Hard (46.62%)
 * Likes:    3218
 * Dislikes: 148
 * Total Accepted:    139.2K
 * Total Submissions: 255.4K
 * Testcase Example:  '[2,4,6,8,10]'
 *
 * Given an integer array nums, return the number of all the arithmetic
 * subsequences of nums.
 *
 * A sequence of numbers is called arithmetic if it consists of at least three
 * elements and if the difference between any two consecutive elements is the
 * same.
 *
 *
 * For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are
 * arithmetic sequences.
 * For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
 *
 *
 * A subsequence of an array is a sequence that can be formed by removing some
 * elements (possibly none) of the array.
 *
 *
 * For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
 *
 *
 * The test cases are generated so that the answer fits in 32-bit integer.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [2,4,6,8,10]
 * Output: 7
 * Explanation: All arithmetic subsequence slices are:
 * [2,4,6]
 * [4,6,8]
 * [6,8,10]
 * [2,4,6,8]
 * [4,6,8,10]
 * [2,4,6,8,10]
 * [2,6,10]
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [7,7,7,7,7]
 * Output: 16
 * Explanation: Any subsequence of this array is arithmetic.
 *
 *
 *
 * Constraints:
 *
 *
 * 1  <= nums.length <= 1000
 * -2^31 <= nums[i] <= 2^31 - 1
 *
 *
 */

// @lc code=start
#include <stdbool.h>
#define MAX_N (1000)

// Brute-force solution
// Just check all possible subsequences (containing more than 2 elements)
// of the original sequence and check them for being arithmetic.
// Works well for short input sequences, but get out of time already for the
// test#39:
// nums = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1], len(nums) = 24
// expected answer 16776915.
/*
bool bits[MAX_N];
int inc(const int n) {
  bool carry = true;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    const bool prev_val = bits[i];
    bits[i] ^= carry;
    carry = carry && prev_val;
    ans += bits[i] ? 1 : 0;
  }
  return ans;
}

int numberOfArithmeticSlices1(const int* nums, const int n) {
  memset(bits, false, sizeof(bits));
  int set_bit_num = 0;
  int ans = 0;
  int i = 0;
  do {
    set_bit_num = inc(n);
    if (set_bit_num < 3) continue;
    i = 0;
    while ((i < n) && !bits[i]) {
      ++i;
    }

    const long a0 = nums[i++];
    while ((i < n) && !bits[i]) {
      ++i;
    };
    long prev = nums[i++];
    const long d = prev - a0;
    do {
      for (; (i < n) && !bits[i]; ++i)
        ;
      if (i >= n) break;
      if ((long)nums[i] - (long)prev != d) break;
      prev = nums[i];
    } while (++i < n);
    ans += (i == n);
  } while (set_bit_num);
  return ans;
}
*/

int numberOfArithmeticSlices(const int* nums, const int n) {
  int ans = 0;
  int stack[MAX_N];
  int top = 0;
  for (int i = 0; i < n - 2; ++i) {
    const long first_num = nums[i];
    for (int j = i + 1; j < n - 1; ++j) {
      const long second_num = nums[j];
      const long d = second_num - first_num;
      if (0 == d) {
        int count = 0;
        for (int k = j + 1; k < n; ++k) {
          count += nums[k] == first_num;
        }
        ans += (1 << count) - 1;
        continue;
      }
      long next_num = second_num + d;
      int start_idx = j + 1;
      do {
        for (int k = start_idx; k < n; ++k) {
          if (nums[k] == next_num) {
            ++ans;
            stack[top++] = k;
            next_num += d;
          }  // next_num found
        }  // k-loop
        if (!top) break;
        const int last_idx = stack[--top];
        next_num = nums[last_idx];
        start_idx = last_idx + 1;
      } while (true);
    }  // j-loop
  }  // i-loop
  return ans;
}

// @lc code=end
