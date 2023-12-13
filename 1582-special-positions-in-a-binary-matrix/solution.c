/*
 * @lc app=leetcode id=1582 lang=c
 *
 * [1582] Special Positions in a Binary Matrix
 *
 * https://leetcode.com/problems/special-positions-in-a-binary-matrix/description/
 *
 * algorithms
 * Easy (65.15%)
 * Likes:    1152
 * Dislikes: 49
 * Total Accepted:    94.8K
 * Total Submissions: 139.2K
 * Testcase Example:  '[[1,0,0],[0,0,1],[1,0,0]]'
 *
 * Given an m x n binary matrix mat, return the number of special positions in
 * mat.
 * 
 * A position (i, j) is called special if mat[i][j] == 1 and all other elements
 * in row i and column j are 0 (rows and columns are 0-indexed).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
 * Output: 1
 * Explanation: (1, 2) is a special position because mat[1][2] == 1 and all
 * other elements in row 1 and column 2 are 0.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
 * Output: 3
 * Explanation: (0, 0), (1, 1) and (2, 2) are special positions.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == mat.length
 * n == mat[i].length
 * 1 <= m, n <= 100
 * mat[i][j] is either 0 or 1.
 * 
 * 
 */

// @lc code=start
#define MAX_WIDTH (128)
#define MAX_HEIGHT (128)
int numSpecial(int** mat, const int rows_num, int* cols_nums) {
  const int cols_num = cols_nums[0];
  char col_sums[MAX_HEIGHT];
  memset(col_sums, -1, sizeof(col_sums));
  int ans = 0;
  for (int i = 0; i < rows_num; ++i) {
    const int* row = mat[i];
    int sum = 0;
    int col_idx = -1;
    for (int j = 0; (j < cols_num); ++j) {
      const int a_ij = *row++;
      sum += a_ij;
      col_idx = a_ij ? j : col_idx;
    }  /* j-loop */
    if (sum != 1) continue;
    if (col_sums[col_idx] < 0) {
      sum = 0;
      for (int j = 0; sum < 2 && j < rows_num; ++j)
        sum += mat[j][col_idx];
      col_sums[col_idx] = sum;
    }
    if (col_sums[col_idx] == 1) ++ans;
  }  /* i-loop */
  return ans;
}// @lc code=end

