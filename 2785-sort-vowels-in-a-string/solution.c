/*
 * @lc app=leetcode id=2785 lang=c
 *
 * [2785] Sort Vowels in a String
 *
 * https://leetcode.com/problems/sort-vowels-in-a-string/description/
 *
 * algorithms
 * Medium (75.36%)
 * Likes:    573
 * Dislikes: 30
 * Total Accepted:    66.5K
 * Total Submissions: 81.7K
 * Testcase Example:  '"lEetcOde"'
 *
 * Given a 0-indexed string s, permute s to get a new string t such that:
 *
 *
 * All consonants remain in their original places. More formally, if there is
 * an index i with 0 <= i < s.length such that s[i] is a consonant, then t[i] =
 * s[i].
 * The vowels must be sorted in the nondecreasing order of their ASCII values.
 * More formally, for pairs of indices i, j with 0 <= i < j < s.length such
 * that s[i] and s[j] are vowels, then t[i] must not have a higher ASCII value
 * than t[j].
 *
 *
 * Return the resulting string.
 *
 * The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in lowercase
 * or uppercase. Consonants comprise all letters that are not vowels.
 *
 *
 * Example 1:
 *
 *
 * Input: s = "lEetcOde"
 * Output: "lEOtcede"
 * Explanation: 'E', 'O', and 'e' are the vowels in s; 'l', 't', 'c', and 'd'
 * are all consonants. The vowels are sorted according to their ASCII values,
 * and the consonants remain in the same places.
 *
 *
 * Example 2:
 *
 *
 * Input: s = "lYmpH"
 * Output: "lYmpH"
 * Explanation: There are no vowels in s (all characters in s are consonants),
 * so we return "lYmpH".
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= s.length <= 10^5
 * s consists only of letters of the English alphabet in uppercase and
 * lowercase.
 *
 *
 */

// @lc code=start

// int compare(const void *a_ptr, const void *b_ptr) {
//   const char a = *(char *)a_ptr;
//   const char b = *(char *)b_ptr;
//   const char a_up = a & ~0x20;
//   const char b_up = b & ~0x20;
//   const bool a_is_vowel = (a_up == 'A') || (a_up == 'E') || (a_up == 'I') ||
//                           (a_up == 'O') || (a_up == 'U');
//   const bool b_is_vowel = (b_up == 'A') || (b_up == 'E') || (b_up == 'I') ||
//                           (b_up == 'O') || (b_up == 'U');
//   int ans = 0;
//   if (a_is_vowel && b_is_vowel)
//     ans = (int)a - (int)b;
//   printf(
//       "a='%c' b='%c' a_up='%c' b_up='%c' a_is_vowel=%d b_is_vowel=%d
//       ans=%d\n", a, b, a_up, b_up, a_is_vowel, b_is_vowel, ans);
//   return ans;
// }

// #define STRING_MAX_LEN (100000)
// int partition(char *str, const int low_idx, const int high_idx) {
//   const char pivot = str[high_idx];
//   int i = low_idx - 1;
//   for (int j = low_idx; j <= high_idx - 1; ++j) {
//     const char sj = str[j];
//     if (sj <= pivot) {
//       str[j] = str[++i];
//       str[i] = sj;
//     }
//   }
//   str[high_idx] = str[++i];
//   str[i] = pivot;
//   return i;
// }

// void quickSort(char *str, int low_idx, int high_idx) {
//   if (low_idx < high_idx) {
//     const int pivot_idx = partition(str, low_idx, high_idx);
//     quickSort(str, low_idx, pivot_idx - 1);
//     quickSort(str, pivot_idx + 1, high_idx);
//   }
// }

char *sortVowels(char *s) {
  char vowels[] = "AEIOUaeiou";
  const int vowels_num = 10;
  bool is_vowel[256];
  memset(is_vowel, 0, sizeof(is_vowel));
  for (int i = 0; i < vowels_num; ++i)
    is_vowel[vowels[i]] = true;

  int char_counts[256];
  memset(char_counts, 0, sizeof(char_counts));
  const int l = strlen(s);
  for (int i = 0; i < l; ++i)
    if (is_vowel[s[i]])
      ++char_counts[s[i]];

  int j = 0;
  for (int i = 0; j < l && i < vowels_num; ++i) {
    const char vowel = vowels[i];
    int vowel_count = char_counts[vowel];
    while (vowel_count && (j < l)) {
      if (is_vowel[s[j]]) {
        s[j] = vowel;
        --vowel_count;
      }
      ++j;
    }
  }
  return s;
}
// @lc code=end
