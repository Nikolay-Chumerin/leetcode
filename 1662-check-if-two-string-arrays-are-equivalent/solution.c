/*
 * @lc app=leetcode id=1662 lang=c
 *
 * [1662] Check If Two String Arrays are Equivalent
 *
 * https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/description/
 *
 * algorithms
 * Easy (83.88%)
 * Likes:    2567
 * Dislikes: 188
 * Total Accepted:    355.6K
 * Total Submissions: 420.8K
 * Testcase Example:  '["ab", "c"]\n["a", "bc"]'
 *
 * Given two string arrays word1 and word2, return true if the two arrays
 * represent the same string, and false otherwise.
 *
 * A string is represented by an array if the array elements concatenated in
 * order forms the string.
 *
 *
 * Example 1:
 *
 *
 * Input: word1 = ["ab", "c"], word2 = ["a", "bc"]
 * Output: true
 * Explanation:
 * word1 represents string "ab" + "c" -> "abc"
 * word2 represents string "a" + "bc" -> "abc"
 * The strings are the same, so return true.
 *
 * Example 2:
 *
 *
 * Input: word1 = ["a", "cb"], word2 = ["ab", "c"]
 * Output: false
 *
 *
 * Example 3:
 *
 *
 * Input: word1  = ["abc", "d", "defg"], word2 = ["abcddefg"]
 * Output: true
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= word1.length, word2.length <= 10^3
 * 1 <= word1[i].length, word2[i].length <= 10^3
 * 1 <= sum(word1[i].length), sum(word2[i].length) <= 10^3
 * word1[i] and word2[i] consist of lowercase letters.
 *
 *
 */

// @lc code=start
bool arrayStringsAreEqual(char **word1, const int word1_len, char **word2,
                          const int word2_len) {
  int i1 = 0;
  int i2 = 0;
  char *p1 = word1[i1];
  char *p2 = word2[i2];
  while (true) {
    // printf("*p1=%c *p2=%c\n", *p1, *p2);
    if (*p1 != *p2)
      return false;

    if (!*(++p1)) {
      if (++i1 >= word1_len) {
        i1 = -1;
      } else
        p1 = word1[i1];
    }

    if (!*(++p2)) {
      if (++i2 >= word2_len) {
        i2 = -1;
      } else
        p2 = word2[i2];
    }

    if (i1 < 0 && i2 < 0)
      return true;
    if ((i1 < 0 && i2 >= 0) && (i1 >= 0 && i2 < 0))
      return false;
  }
}
// @lc code=end
