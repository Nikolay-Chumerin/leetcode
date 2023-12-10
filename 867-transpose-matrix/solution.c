/*
 * @lc app=leetcode id=867 lang=c
 *
 * [867] Transpose Matrix
 *
 * https://leetcode.com/problems/transpose-matrix/description/
 *
 * algorithms
 * Easy (66.06%)
 * Likes:    3558
 * Dislikes: 438
 * Total Accepted:    351.4K
 * Total Submissions: 501K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * Given a 2D integer array matrix, return the transpose of matrix.
 *
 * The transpose of a matrix is the matrix flipped over its main diagonal,
 * switching the matrix's row and column indices.
 *
 *
 * Example 1:
 * Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [[1,4,7],[2,5,8],[3,6,9]]
 *
 *
 * Example 2:
 * Input: matrix = [[1,2,3],[4,5,6]]
 * Output: [[1,4],[2,5],[3,6]]
 *
 *
 *
 * Constraints:
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 1000
 * 1 <= m * n <= 10^5
 * -10^9 <= matrix[i][j] <= 10^9
 *
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **transpose(int **inp_mat, const int inp_rows_num, int *inp_col_nums,
                int *out_rows_num_ptr, int **out_col_nums) {
  const int inp_cols_num = inp_col_nums[0];
  const int out_rows_num = inp_cols_num;
  const int out_cols_num = inp_rows_num;
  *out_rows_num_ptr = out_rows_num;
  *out_col_nums = (int *)malloc(out_rows_num * sizeof(int *));
  int **out_mat = (int **)malloc(out_rows_num * sizeof(int *));
  for (int i = 0; i < out_rows_num; ++i) {
    (*out_col_nums)[i] = out_cols_num;
    out_mat[i] = (int *)malloc(out_cols_num * sizeof(int *));
  }

  for (int i = 0; i < inp_rows_num; ++i) {
    for (int j = 0; j < inp_cols_num; ++j) {
      out_mat[j][i] = inp_mat[i][j];
    } /* j-loop */
  }   /* i-loop */
  return out_mat;
}  // @lc code=end
