/*
 * @lc app=leetcode id=66 lang=c
 *
 * [66] Plus One
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *plusOne(int *digits, int digits_len, int *ans_len) {
  int carry = 1;
  int src_idx = digits_len;
  while (--src_idx >= 0) {
    digits[src_idx] += carry;
    if (digits[src_idx] > 9) {
      digits[src_idx] -= 10;
      carry = 1;
    } else
      carry = 0;
  }

  *ans_len = carry + digits_len;
  int *ans = malloc((*ans_len) * sizeof(int));
  int dst_idx = 0;
  if (carry) {
    ans[0] = 1;
    ++dst_idx;
  }
  memcpy(&ans[dst_idx], digits, sizeof(int) * digits_len);
  return ans;
}
// @lc code=end
