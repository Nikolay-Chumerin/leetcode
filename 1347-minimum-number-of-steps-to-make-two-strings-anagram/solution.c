/*
 * @lc app=leetcode id=1347 lang=c
 *
 * [1347] Minimum Number of Steps to Make Two Strings Anagram
 *
 * https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/description/
 *
 * algorithms
 * Medium (78.19%)
 * Likes:    2318
 * Dislikes: 98
 * Total Accepted:    191.6K
 * Total Submissions: 238.1K
 * Testcase Example:  '"bab"\n"aba"'
 *
 * You are given two strings of the same length s and t. In one step you can
 * choose any character of t and replace it with another character.
 * 
 * Return the minimum number of steps to make t an anagram of s.
 * 
 * An Anagram of a string is a string that contains the same characters with a
 * different (or the same) ordering.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "bab", t = "aba"
 * Output: 1
 * Explanation: Replace the first 'a' in t with b, t = "bba" which is anagram
 * of s.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "leetcode", t = "practice"
 * Output: 5
 * Explanation: Replace 'p', 'r', 'a', 'i' and 'c' from t with proper
 * characters to make t anagram of s.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "anagram", t = "mangaar"
 * Output: 0
 * Explanation: "anagram" and "mangaar" are anagrams. 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 5 * 10^4
 * s.length == t.length
 * s and t consist of lowercase English letters only.
 * 
 * 
 */

// @lc code=start
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize(-flto, -ffast-math, -march=native, -mtune=native)

int minSteps(char* s, char* t) {
  int h[128] = {0};
  while (*s) {
    ++h[*s++];
    --h[*t++];
  }

  int ans = 0;
  for (int i = 'Z'; i <= 'z'; ++i)
    ans += h[i] > 0 ? h[i] : -h[i];

  return ans / 2;
}  // @lc code=end

