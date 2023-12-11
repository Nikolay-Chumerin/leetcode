/*
 * @lc app=leetcode id=1287 lang=c
 *
 * [1287] Element Appearing More Than 25% In Sorted Array
 *
 * https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/description/
 *
 * algorithms
 * Easy (59.08%)
 * Likes:    1414
 * Dislikes: 65
 * Total Accepted:    151.9K
 * Total Submissions: 249.4K
 * Testcase Example:  '[1,2,2,6,6,6,6,7,10]'
 *
 * Given an integer array sorted in non-decreasing order, there is exactly one
 * integer in the array that occurs more than 25% of the time, return that
 * integer.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,2,2,6,6,6,6,7,10]
 * Output: 6
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [1,1]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 10^4
 * 0 <= arr[i] <= 10^5
 * 
 * 
 */

// @lc code=start
#pragma GCC optimize("O3","unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC optimize(-flto, -ffast-math, -march=native, -mtune=native)
int findSpecialInteger(int* a, const int len) {
  int *b = a + (len >> 2);
  while (*a - *b++) ++a;
  return *a;
}
// @lc code=end

