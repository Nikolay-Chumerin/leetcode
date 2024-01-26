/*
 * @lc app=leetcode id=576 lang=c
 *
 * [576] Out of Boundary Paths
 *
 * https://leetcode.com/problems/out-of-boundary-paths/description/
 *
 * algorithms
 * Medium (44.23%)
 * Likes:    3558
 * Dislikes: 266
 * Total Accepted:    161.1K
 * Total Submissions: 348.6K
 * Testcase Example:  '2\n2\n2\n0\n0'
 *
 * There is an m x n grid with a ball. The ball is initially at the position
 * [startRow, startColumn]. You are allowed to move the ball to one of the four
 * adjacent cells in the grid (possibly out of the grid crossing the grid
 * boundary). You can apply at most maxMove moves to the ball.
 *
 * Given the five integers m, n, maxMove, startRow, startColumn, return the
 * number of paths to move the ball out of the grid boundary. Since the answer
 * can be very large, return it modulo 10^9 + 7.
 *
 *
 * Example 1:
 *
 *
 * Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
 * Output: 6
 *
 *
 * Example 2:
 *
 *
 * Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
 * Output: 12
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= m, n <= 50
 * 0 <= maxMove <= 50
 * 0 <= startRow < m
 * 0 <= startColumn < n
 *
 *
 */

// @lc code=start
#define MAX_N (50)
#define MOD (1000000007)
uint64_t p[2][MAX_N + 2][MAX_N + 2];

int findPaths(const int m, const int n, const int moves_max_num,
              const int start_row, const int start_col) {
  memset(p, 0, sizeof(p));
  for (int k = 0; k < 2; ++k) {
    for (int i = 1; i <= n; ++i) {
      p[k][0][i] = p[k][m + 1][i] = 1;
    }  // i-loop
    for (int j = 1; j <= m; ++j) {
      p[k][j][0] = p[k][j][n + 1] = 1;
    }  // j-loop
  }    // k-loop
  // print(m, n);
  int curr = 0;
  int prev = 1;

  for (int move_idx = 0; move_idx < moves_max_num; ++move_idx) {
    curr ^= 1;
    prev ^= 1;
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        p[curr][i][j] = (p[prev][i - 1][j] + p[prev][i + 1][j] +
                         p[prev][i][j - 1] + p[prev][i][j + 1]) %
                        MOD;
      }  // loop over cols
    }    // loop over rows
  }      // loop over moves

  return p[curr][start_row + 1][start_col + 1];
}  // @lc code=end
