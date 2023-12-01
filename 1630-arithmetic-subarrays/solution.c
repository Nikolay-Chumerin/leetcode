/*
 * @lc app=leetcode id=1630 lang=c
 *
 * [1630] Arithmetic Subarrays
 *
 * https://leetcode.com/problems/arithmetic-subarrays/description/
 *
 * algorithms
 * Medium (80.98%)
 * Likes:    1443
 * Dislikes: 158
 * Total Accepted:    89K
 * Total Submissions: 107.2K
 * Testcase Example:  '[4,6,5,9,3,7]\n[0,0,2]\n[2,3,5]'
 *
 * A sequence of numbers is called arithmetic if it consists of at least two
 * elements, and the difference between every two consecutive elements is the
 * same. More formally, a sequence s is arithmetic if and only if s[i+1] - s[i]
 * == s[1] - s[0] for all valid i.
 *
 * For example, these are arithmetic sequences:
 *
 *
 * 1, 3, 5, 7, 9
 * 7, 7, 7, 7
 * 3, -1, -5, -9
 *
 * The following sequence is not arithmetic:
 *
 *
 * 1, 1, 2, 5, 7
 *
 * You are given an array of n integers, nums, and two arrays of m integers
 * each, l and r, representing the m range queries, where the i^th query is the
 * range [l[i], r[i]]. All the arrays are 0-indexed.
 *
 * Return a list of boolean elements answer, where answer[i] is true if the
 * subarray nums[l[i]], nums[l[i]+1], ... , nums[r[i]] can be rearranged to
 * form an arithmetic sequence, and false otherwise.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [4,6,5,9,3,7], l = [0,0,2], r = [2,3,5]
 * Output: [true,false,true]
 * Explanation:
 * In the 0^th query, the subarray is [4,6,5]. This can be rearranged as
 * [6,5,4], which is an arithmetic sequence.
 * In the 1^st query, the subarray is [4,6,5,9]. This cannot be rearranged as
 * an arithmetic sequence.
 * In the 2^nd query, the subarray is [5,9,3,7]. This can be rearranged as
 * [3,5,7,9], which is an arithmetic sequence.
 *
 * Example 2:
 *
 *
 * Input: nums = [-12,-9,-3,-12,-6,15,20,-25,-20,-15,-10], l = [0,1,6,4,8,7], r
 * = [4,4,9,7,9,10]
 * Output: [false,true,false,false,true,true]
 *
 *
 *
 * Constraints:
 *
 *
 * n == nums.length
 * m == l.length
 * m == r.length
 * 2 <= n <= 500
 * 1 <= m <= 500
 * 0 <= l[i] < r[i] < n
 * -10^5 <= nums[i] <= 10^5
 *
 *
 */ 

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_LEN (500)
bool is_arithmetic_progression(const int *arr, const int len) {
  if (len < 2)
    return false;
  int max = arr[0];
  int min = arr[0];
  int sum = 0;
  for (int i = 0; i < len; ++i) {
    const int a = arr[i];
    sum += a;
    if (a > max)
      max = a;
    if (a < min)
      min = a;
  }
  /* Constant sequence check. */
  if (min == max)
    return true;

  /* Actual sum should be equal to the arithmetic progression sum formula. */
  if (sum != len * (min + max) / 2)
    return false;

  /* Arithmetic progression delta (increment/decrement). */
  const int d = (max - min) / (len - 1);

  /* Delta must be integer. */
  if (min + d * (len - 1) != max) /* will fail if d is not integer */
    return false;

  /* Let's check if indices of the provided range are filling the range [0, ...
    , n-1]. To do this let's use a set, implemented using a boolean array.
  */
  bool present[MAX_LEN];
  memset(present, false, sizeof(present));

  /* Let's iterate over the input array elements, estimate index of each, and
  check if this index hasn't been used already. If it was - return false,
  otherwise add it to the set and increment number of unique indices.
  */
  int found = 0;
  for (int i = 0; i < len; ++i) {
    const int idx = (arr[i] - min) / d;
    if (present[idx])
      return false;
    present[idx] = true;
    ++found;
  }
  return found == len;
}

bool *checkArithmeticSubarrays(const int *nums, const int n, const int *l,
                               const int l_len, const int *r, const int r_len,
                               int *ans_len) {
  *ans_len = l_len;
  bool *ans = malloc((*ans_len) * sizeof(*ans));

  for (int i = 0; i < l_len; ++i)
    ans[i] = is_arithmetic_progression(nums + l[i], r[i] - l[i] + 1);
  return ans;
}
// @lc code=end
