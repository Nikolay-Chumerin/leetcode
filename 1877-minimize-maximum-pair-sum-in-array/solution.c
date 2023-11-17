/*
 * @lc app=leetcode id=1877 lang=c
 *
 * [1877] Minimize Maximum Pair Sum in Array
 *
 * https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/description/
 *
 * algorithms
 * Medium (79.69%)
 * Likes:    1648
 * Dislikes: 360
 * Total Accepted:    128.3K
 * Total Submissions: 157.7K
 * Testcase Example:  '[3,5,2,3]'
 *
 * The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the
 * largest pair sum in a list of pairs.
 *
 *
 * For example, if we have pairs (1,5), (2,3), and (4,4), the maximum pair sum
 * would be max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8.
 *
 *
 * Given an array nums of even length n, pair up the elements of nums into n /
 * 2 pairs such that:
 *
 *
 * Each element of nums is in exactly one pair, and
 * The maximum pair sum is minimized.
 *
 *
 * Return the minimized maximum pair sum after optimally pairing up the
 * elements.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [3,5,2,3]
 * Output: 7
 * Explanation: The elements can be paired up into pairs (3,3) and (5,2).
 * The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [3,5,4,2,4,6]
 * Output: 8
 * Explanation: The elements can be paired up into pairs (3,5), (4,4), and
 * (6,2).
 * The maximum pair sum is max(3+5, 4+4, 6+2) = max(8, 8, 8) = 8.
 *
 *
 *
 * Constraints:
 *
 *
 * n == nums.length
 * 2 <= n <= 10^5
 * n is even.
 * 1 <= nums[i] <= 10^5
 *
 */

// @lc code=start

void quicksort(int *arr, const int start, const int end) {
  if (start >= end)
    return;
  const int pivot = arr[end];
  int i = start;
  for (int j = start; j <= end; ++j) {
    const int aj = arr[j];
    if (aj >= pivot)
      continue;
    arr[j] = arr[i];
    arr[i++] = aj;
  }
  arr[end] = arr[i];
  arr[i] = pivot;
  quicksort(arr, start, i - 1);
  quicksort(arr, i + 1, end);
}  /* quicksort(...) */

int minPairSum(int *nums, int n) {
  quicksort(nums, 0, n - 1);
  int max = nums[0] + nums[n - 1];
  for (int i = 1; i < n / 2; ++i) {
    const int sum = nums[i] + nums[n - i - 1];
    max = (sum > max) ? sum : max;
  }
  return max;
}
// @lc code=end
