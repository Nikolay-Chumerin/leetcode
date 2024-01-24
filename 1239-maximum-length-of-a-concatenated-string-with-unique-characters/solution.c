/*
 * @lc app=leetcode id=1239 lang=c
 *
 * [1239] Maximum Length of a Concatenated String with Unique Characters
 *
 * https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/description/
 *
 * algorithms
 * Medium (52.17%)
 * Likes:    4304
 * Dislikes: 318
 * Total Accepted:    272.1K
 * Total Submissions: 502.6K
 * Testcase Example:  '["un","iq","ue"]'
 *
 * You are given an array of strings arr. A string s is formed by the
 * concatenation of a subsequence of arr that has unique characters.
 * 
 * Return the maximum possible length of s.
 * 
 * A subsequence is an array that can be derived from another array by deleting
 * some or no elements without changing the order of the remaining elements.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = ["un","iq","ue"]
 * Output: 4
 * Explanation: All the valid concatenations are:
 * - ""
 * - "un"
 * - "iq"
 * - "ue"
 * - "uniq" ("un" + "iq")
 * - "ique" ("iq" + "ue")
 * Maximum length is 4.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = ["cha","r","act","ers"]
 * Output: 6
 * Explanation: Possible longest valid concatenations are "chaers" ("cha" +
 * "ers") and "acters" ("act" + "ers").
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
 * Output: 26
 * Explanation: The only string in arr has all 26 characters.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 16
 * 1 <= arr[i].length <= 26
 * arr[i] contains only lowercase English letters.
 * 
 * 
 */

// @lc code=start
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize(-flto, -ffast-math, -march=native, -mtune=native)

#define MAX_N (16)
typedef uint32_t mask_t;
//------------------------------------------------------------------------------
void set_word_bit_masks(char** words, const int n, mask_t* masks) {
  for (int i = 0; i < n; ++i) {
    char *s = words[i];
    masks[i] = 0;
    do {
      const uint32_t bit_mask = 1 << (*s - 'a');
      if (bit_mask & masks[i]) {
        masks[i] = 0;
        break;
      }
      masks[i] |= bit_mask;
    } while (*(++s));
  }
}  // set_word_bit_masks(...)
//------------------------------------------------------------------------------
mask_t get_combination_mask(int combination, const int n, const mask_t* masks) {
  mask_t mask = 0;
  for (int j = 0; j < n; ++j, combination >>= 1) {
    if ((combination & 1) == 0) continue;  // skip 0-bit
    if (mask & masks[j])  // mask overlap detected
      return 0U;
    mask += masks[j];
  }  // loop over bits in combination
  return mask;
}  // combination_mask(...)
//------------------------------------------------------------------------------
int maxLength(char** words, const int words_num) {
  mask_t masks[MAX_N + 1];
  int ans = 0;
  set_word_bit_masks(words, words_num, masks);
  const int combinations_num = (1 << words_num);  // 2^words_num
  for (int combination = 0; combination < combinations_num; ++combination) {
    const mask_t mask = get_combination_mask(combination, words_num, masks);
    const int unique_chars_num = __builtin_popcount(mask);  // number of 1-bits
    if (ans > unique_chars_num) continue;
    ans = unique_chars_num;
  }  // loop over all word combinations
 
  return ans;
}  // maxLength(..)// @lc code=end

