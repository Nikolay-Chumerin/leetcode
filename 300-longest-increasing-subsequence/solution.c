/*
 * @lc app=leetcode id=300 lang=c
 *
 * [300] Longest Increasing Subsequence
 *
 * https://leetcode.com/problems/longest-increasing-subsequence/description/
 *
 * algorithms
 * Medium (53.57%)
 * Likes:    20243
 * Dislikes: 409
 * Total Accepted:    1.5M
 * Total Submissions: 2.8M
 * Testcase Example:  '[10,9,2,5,3,7,101,18]'
 *
 * Given an integer array nums, return the length of the longest strictly
 * increasing subsequence.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [10,9,2,5,3,7,101,18]
 * Output: 4
 * Explanation: The longest increasing subsequence is [2,3,7,101], therefore
 * the length is 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,1,0,3,2,3]
 * Output: 4
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [7,7,7,7,7,7,7]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 2500
 * -10^4 <= nums[i] <= 10^4
 * 
 * 
 * 
 * Follow up: Can you come up with an algorithm that runs in O(n log(n)) time
 * complexity?
 * 
 */

// @lc code=start

/* Dynamic Programming O(n^2) solution */
int lengthOfLIS(const int* nums, const int n) {
  int sols[n + 1];
  int ans = 1;
  for (int i = 0; i < n; ++i) {
    sols[i] = 1;
    const int num = nums[i];
    int best_len = 0;
    for (int j = 0; j < i; ++j) {
      if ((nums[j] < num) && ((sols[j] + 1) > sols[i]))
        sols[i] =  sols[j] + 1;
    }  // inner j-loop
    if (ans < sols[i]) ans = sols[i];
  }  // main i-loop
  return ans;
}

/* Backtracking solution */
#define MAX_N (2500)
int lengthOfLIS_backtrack(const int* nums, const int n) {
  printf("------[n = %d]------------\n", n);
  int stack[MAX_N];
  int stack_size = 0;
  
  int idx = 0;
  int ans = 1;
  stack[stack_size++] = idx;
  int last;
  while (stack_size > 0) {
    last = nums[stack[stack_size - 1]];
    while ((idx < n) && (idx < (n - ans + stack_size))) {
      if (nums[idx] > last) {
        stack[stack_size++] = idx;
        last = nums[idx];
      }
      ++idx;
    }  // loop over nums
    if (stack_size > ans) {
      ans = stack_size;
    }
    if (ans == n) break;
    do {
      idx = stack[--stack_size] + 1;
      if (stack_size >= 0 && idx < n) break;
    } while (stack_size > 0);
    if (stack_size == 0 && idx < n) {
      stack[stack_size++] = idx;
    }
  }  // main loop
  return ans;
}// @lc code=end