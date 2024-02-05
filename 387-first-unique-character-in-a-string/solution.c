/*
 * @lc app=leetcode id=387 lang=c
 *
 * [387] First Unique Character in a String
 *
 * https://leetcode.com/problems/first-unique-character-in-a-string/description/
 *
 * algorithms
 * Easy (60.56%)
 * Likes:    8605
 * Dislikes: 279
 * Total Accepted:    1.6M
 * Total Submissions: 2.6M
 * Testcase Example:  '"leetcode"'
 *
 * Given a string s, find the first non-repeating character in it and return
 * its index. If it does not exist, return -1.
 *
 *
 * Example 1:
 * Input: s = "leetcode"
 * Output: 0
 * Example 2:
 * Input: s = "loveleetcode"
 * Output: 2
 * Example 3:
 * Input: s = "aabb"
 * Output: -1
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 10^5
 * s consists of only lowercase English letters.
 *
 *
 */

// @lc code=start
int32_t firstUniqChar(const uint8_t* s) {
  uint32_t counts['z' + 1] = {0};
  for (int32_t i = 0; s[i]; ++i) ++counts[s[i]];

  for (int32_t i = 0; s[i]; ++i)
    if (1 == counts[s[i]]) return i;

  return -1;
}
// @lc code=end
