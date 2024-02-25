/*
 * @lc app=leetcode id=2709 lang=c
 *
 * [2709] Greatest Common Divisor Traversal
 *
 * https://leetcode.com/problems/greatest-common-divisor-traversal/description/
 *
 * algorithms
 * Hard (22.95%)
 * Likes:    694
 * Dislikes: 111
 * Total Accepted:    55.8K
 * Total Submissions: 129.4K
 * Testcase Example:  '[2,3,6]'
 *
 * You are given a 0-indexed integer array nums, and you are allowed to
 * traverse between its indices. You can traverse between index i and index j,
 * i != j, if and only if gcd(nums[i], nums[j]) > 1, where gcd is the greatest
 * common divisor.
 *
 * Your task is to determine if for every pair of indices i and j in nums,
 * where i < j, there exists a sequence of traversals that can take us from i
 * to j.
 *
 * Return true if it is possible to traverse between all such pairs of indices,
 * or false otherwise.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [2,3,6]
 * Output: true
 * Explanation: In this example, there are 3 possible pairs of indices: (0, 1),
 * (0, 2), and (1, 2).
 * To go from index 0 to index 1, we can use the sequence of traversals 0 -> 2
 * -> 1, where we move from index 0 to index 2 because gcd(nums[0], nums[2]) =
 * gcd(2, 6) = 2 > 1, and then move from index 2 to index 1 because
 * gcd(nums[2], nums[1]) = gcd(6, 3) = 3 > 1.
 * To go from index 0 to index 2, we can just go directly because gcd(nums[0],
 * nums[2]) = gcd(2, 6) = 2 > 1. Likewise, to go from index 1 to index 2, we
 * can just go directly because gcd(nums[1], nums[2]) = gcd(3, 6) = 3 > 1.
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [3,9,5]
 * Output: false
 * Explanation: No sequence of traversals can take us from index 0 to index 2
 * in this example. So, we return false.
 *
 *
 * Example 3:
 *
 *
 * Input: nums = [4,3,12,8]
 * Output: true
 * Explanation: There are 6 possible pairs of indices to traverse between: (0,
 * 1), (0, 2), (0, 3), (1, 2), (1, 3), and (2, 3). A valid sequence of
 * traversals exists for each pair, so we return true.
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^5
 *
 *
 */

// @lc code=start
#define N (100000)

int compare_ints(const void* a, const void* b) { return *(int*)a - *(int*)b; }

bool canTraverseAllPairs(int* nums, int n) {
  qsort(nums, n, sizeof(nums[0]), compare_ints);
  if (1 == n) return true;
  if (1 == nums[0]) return false;
  bool div_set[N + 1];
  int div_list[N + 1];
  int prev_n = 0;
  int new_n = 0;
  for (int i = 0; i < n; ++i) {
    if ((new_n > 0) && (nums[new_n - 1] == nums[i])) continue;
    nums[new_n++] = nums[i];
  }
  if (1 == new_n) return true;
  int max_num = nums[new_n - 1];
  memset(div_set, false, sizeof(div_set));

  bool intersect_init = true;
  bool found_at_least_one = false;
  do {
    prev_n = new_n;
    new_n = 0;
    for (int i = 0; i < prev_n; ++i) {
      int div_n = 0;
      int num = nums[i];
      if ((1 == num) || ((i > 0) && (nums[i - 1] == num))) continue;
      bool intersect = intersect_init;
      int j = 1;
      int divs_num = 0;
      while (++j <= num) {
        if (num % j) continue;
        while (0 == (num % j)) {
          num /= j;
          ++divs_num;
        }
        div_list[div_n++] = j;
        intersect |= div_set[j];
      }
      if ((divs_num == 1) && (nums[i] > (max_num / 2))) return false;
      if (intersect) {
        for (int j = 0; j < div_n; ++j) {
          div_set[div_list[j]] = true;
        }  // j-loop
        found_at_least_one = true;
      } else {
        nums[new_n++] = nums[i];
      }
      intersect_init = false;
    }  // i-loop
  } while (prev_n != new_n);
  return found_at_least_one && (0 == new_n);
}
// @lc code=end
