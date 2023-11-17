/*
 * @lc app=leetcode id=1887 lang=c
 *
 * [1887] Reduction Operations to Make the Array Elements Equal
 *
 * https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/description/
 *
 * algorithms
 * Medium (62.73%)
 * Likes:    910
 * Dislikes: 41
 * Total Accepted:    58.8K
 * Total Submissions: 81.7K
 * Testcase Example:  '[5,1,3]'
 *
 * Given an integer array nums, your goal is to make all elements in nums
 * equal. To complete one operation, follow these steps:
 * 
 * 
 * Find the largest value in nums. Let its index be i (0-indexed) and its value
 * be largest. If there are multiple elements with the largest value, pick the
 * smallest i.
 * Find the next largest value in nums strictly smaller than largest. Let its
 * value be nextLargest.
 * Reduce nums[i] to nextLargest.
 * 
 * 
 * e3Return the number of operations to make all elements in nums equal.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [5,1,3]
 * Output: 3
 * Explanation: It takes 3 operations to make all elements in nums equal:
 * 1. largest = 5 at index 0. nextLargest = 3. Reduce nums[0] to 3. nums =
 * [3,1,3].
 * 2. largest = 3 at index 0. nextLargest = 1. Reduce nums[0] to 1. nums =
 * [1,1,3].
 * 3. largest = 3 at index 2. nextLargest = 1. Reduce nums[2] to 1. nums =
 * [1,1,1].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,1,1]
 * Output: 0
 * Explanation: All elements in nums are already equal.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,1,2,2,3]
 * Output: 4
 * Explanation: It takes 4 operations to make all elements in nums equal:
 * 1. largest = 3 at index 4. nextLargest = 2. Reduce nums[4] to 2. nums =
 * [1,1,2,2,2].
 * 2. largest = 2 at index 2. nextLargest = 1. Reduce nums[2] to 1. nums =
 * [1,1,1,2,2]. 
 * 3. largest = 2 at index 3. nextLargest = 1. Reduce nums[3] to 1. nums =
 * [1,1,1,1,2].
 * 4. largest = 2 at index 4. nextLargest = 1. Reduce nums[4] to 1. nums =
 * [1,1,1,1,1].
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 5 * 10^4
 * 1 <= nums[i] <= 5 * 10^4
 * 
 * 
 */

// @lc code=start
#pragma GCC optimize("O3,Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

#define MAX_NUM (50000)
#define MIN(a, b) (b + ((a - b) & (a - b) >> 31))
#define MAX(a, b) (a - ((a - b) & (a - b) >> 31))
int reductionOperations(int* nums, const int n) {
  int counts[MAX_NUM + 1] = {0};
  int i, j, ans = 0, min = nums[0], max = nums[0];
  for (i = 0; i < n; ++i) {
    const int num = nums[i];
    min = MIN(min, num);
    max = MAX(max, num);
    ++counts[num];
  }
  i = min + 1;
  j = counts[min] - 1;
  for (; i <= max; ++i) {
    const int count = counts[i];
    if (count) {
      ans += n - j - 1;
      j += count;
    }
  }
  return ans;
}
// @lc code=end
