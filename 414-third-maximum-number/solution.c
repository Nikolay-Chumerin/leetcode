/*
 * @lc app=leetcode id=414 lang=c
 *
 * [414] Third Maximum Number
 *
 * https://leetcode.com/problems/third-maximum-number/description/
 *
 * algorithms
 * Easy (34.04%)
 * Likes:    2849
 * Dislikes: 2999
 * Total Accepted:    481.3K
 * Total Submissions: 1.4M
 * Testcase Example:  '[3,2,1]'
 *
 * Given an integer array nums, return the third distinct maximum number in
 * this array. If the third maximum does not exist, return the maximum
 * number.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,2,1]
 * Output: 1
 * Explanation:
 * The first distinct maximum is 3.
 * The second distinct maximum is 2.
 * The third distinct maximum is 1.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2]
 * Output: 2
 * Explanation:
 * The first distinct maximum is 2.
 * The second distinct maximum is 1.
 * The third distinct maximum does not exist, so the maximum (2) is returned
 * instead.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [2,2,3,1]
 * Output: 1
 * Explanation:
 * The first distinct maximum is 3.
 * The second distinct maximum is 2 (both 2's are counted together since they
 * have the same value).
 * The third distinct maximum is 1.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^4
 * -2^31 <= nums[i] <= 2^31 - 1
 * 
 * 
 * 
 * Follow up: Can you find an O(n) solution?
 */

// @lc code=start
int thirdMax(int* nums, int n) {
  long int n1, n2, n3;
  n1 = n2 = n3 = LONG_MIN;
  bool found = false;
  for (int i = 0; i < n; ++i) {
    const int ni = nums[i];
    if (n1 < ni) {
      n3 = n2;
      n2 = n1;
      n1 = ni;
    } else if (n2 < ni && ni < n1) {
      n3 = n2;
      n2 = ni;
    } else if (n3 < ni && ni < n2 && ni < n1) {
      n3 = ni;
    }
  }
  return (n3 == LONG_MIN) ? n1 : n3;
}
// @lc code=end

