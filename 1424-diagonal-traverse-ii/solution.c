/*
 * @lc app=leetcode id=1424 lang=c
 *
 * [1424] Diagonal Traverse II
 *
 * https://leetcode.com/problems/diagonal-traverse-ii/description/
 *
 * algorithms
 * Medium (50.84%)
 * Likes:    1516
 * Dislikes: 121
 * Total Accepted:    78.5K
 * Total Submissions: 145.7K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * Given a 2D integer array nums, return all elements of nums in diagonal order
 * as shown in the below images.
 *
 *
 * Example 1:
 *
 *
 * Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [1,4,2,7,5,3,8,6,9]
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
 * Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i].length <= 10^5
 * 1 <= sum(nums[i].length) <= 10^5
 * 1 <= nums[i][j] <= 10^5
 *
 *
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findDiagonalOrder2(int **nums, int rows_num, int *row_lens, int *ans_len) {
  int cols_num = 0;
  for (int i = 0; i < rows_num; ++i) {
    const int row_len = row_lens[i];
    if (cols_num < row_len)
      cols_num = row_len;
  }
  int *ans = malloc((cols_num * rows_num) * sizeof(int));
  int idx = 0; /* index of element: in range [0, ... , (*ans) - 1] */
  int start_row_idx, start_col_idx, diag_idx;
  /* Go down first */
  for (start_row_idx = 0; start_row_idx < rows_num; ++start_row_idx) {
    for (diag_idx = 0; diag_idx <= start_row_idx; ++diag_idx) {
      const int row_idx = start_row_idx - diag_idx;
      const int col_idx = diag_idx;
      if (col_idx >= row_lens[row_idx])
        continue;
      ans[idx++] = nums[row_idx][col_idx];
    } /* loop over columns */
  }   /* loop over rows */

  /* Go right */
  start_row_idx = rows_num - 1;
  for (start_col_idx = 1; start_col_idx < cols_num; ++start_col_idx) {
    for (diag_idx = 0; diag_idx < rows_num; ++diag_idx) {
      const int row_idx = start_row_idx - diag_idx;
      const int col_idx = start_col_idx + diag_idx;
      if (row_idx < 0 || row_idx >= rows_num || col_idx < 0 ||
          col_idx >= row_lens[row_idx])
        continue;
      ans[idx++] = nums[row_idx][col_idx];
    } /* loop over columns */
  }   /* loop over rows */
  *ans_len = idx;
  return ans;
}

/*****************************************************************************/
#define ROW_COEFF (100000)
#define COL_COEFF (100001)

int comp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int *findDiagonalOrder(int **nums, int rows_num, int *row_lens, int *ans_len) {
  int nums_num = 0;
  for (int i = 0; i < rows_num; ++i)
    nums_num += row_lens[i];

  int *ans = malloc(nums_num * sizeof(int));
  *ans = nums_num;

  int idx = 0;
  for (int i = 0; i < rows_num; ++i) {
    const int row_term = ROW_COEFF * i;
    for (int j = 0; row_lens[i]; ++j) {
      ans[idx++] = row_term + COL_COEFF * j;
    } /* j-loop */
  }   /* i-loop */

  qsort(ans, nums_num, sizeof(ans[0]), comp);
  
  for (int i = 0; i < nums_num; ++i) {
    const int idx = ans[i];
    const int col_idx = idx % ROW_COEFF;
    const int row_idx = (idx - col_idx * ROW_COEFF) / COL_COEFF;
    printf("(%d,%d) ", row_idx, col_idx);
    ans[i] = nums[row_idx][col_idx];
  }
  return ans;
}

// @lc code=end
