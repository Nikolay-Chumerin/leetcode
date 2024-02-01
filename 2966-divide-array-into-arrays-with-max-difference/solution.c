/*
 * @lc app=leetcode id=2966 lang=c
 *
 * [2966] Divide Array Into Arrays With Max Difference
 *
 * https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/description/
 *
 * algorithms
 * Medium (68.51%)
 * Likes:    399
 * Dislikes: 99
 * Total Accepted:    70.4K
 * Total Submissions: 102.8K
 * Testcase Example:  '[1,3,4,8,7,9,3,5,1]\n2'
 *
 * You are given an integer array nums of size n and a positive integer k.
 *
 * Divide the array into one or more arrays of size 3 satisfying the following
 * conditions:
 *
 *
 * Each element of nums should be in exactly one array.
 * The difference between any two elements in one array is less than or equal
 * to k.
 *
 *
 * Return a 2D array containing all the arrays. If it is impossible to satisfy
 * the conditions, return an empty array. And if there are multiple answers,
 * return any of them.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [1,3,4,8,7,9,3,5,1], k = 2
 * Output: [[1,1,3],[3,4,5],[7,8,9]]
 * Explanation: We can divide the array into the following arrays: [1,1,3],
 * [3,4,5] and [7,8,9].
 * The difference between any two elements in each array is less than or equal
 * to 2.
 * Note that the order of elements is not important.
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [1,3,3,2,7,3], k = 3
 * Output: []
 * Explanation: It is not possible to divide the array satisfying all the
 * conditions.
 *
 *
 *
 * Constraints:
 *
 *
 * n == nums.length
 * 1 <= n <= 10^5
 * n is a multiple of 3.
 * 1 <= nums[i] <= 10^5
 * 1 <= k <= 10^5
 *
 *
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
#pragma GCC optimize("O3", "unroll-loops")

int comp(const void* a, const void* b) { return *(int*)a - *(int*)b; }

int** divideArray(int* nums, const int n, int k, int* out_n,
                  int** out_cols_nums) {
  qsort(nums, n, sizeof(int), comp);
  const int expected_triplets_num = n / 3;
  int* a = nums;
  for (int i = 0; i < expected_triplets_num; ++i, a += 3) {
    if ((a[2] - a[0]) > k) {
      return *out_n = *out_cols_nums = NULL;
    }
  }
  int** ans = malloc(expected_triplets_num * sizeof(int*));
  *out_cols_nums = malloc(expected_triplets_num * sizeof(int));
  *out_n = expected_triplets_num;
  for (int i = 0; i < expected_triplets_num; ++i) {
    a = ans[i] = malloc(3 * sizeof(int));
    (*out_cols_nums)[i] = 3;
    for (int j = 0; j < 3; ++j) *a++ = *nums++;
  }
  return ans;
}  // @lc code=end
