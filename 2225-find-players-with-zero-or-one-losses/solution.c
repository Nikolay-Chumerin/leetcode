/*
 * @lc app=leetcode id=2225 lang=c
 *
 * [2225] Find Players With Zero or One Losses
 *
 * https://leetcode.com/problems/find-players-with-zero-or-one-losses/description/
 *
 * algorithms
 * Medium (71.14%)
 * Likes:    1746
 * Dislikes: 124
 * Total Accepted:    153.2K
 * Total Submissions: 210.3K
 * Testcase Example:
 * '[[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]'
 *
 * You are given an integer array matches where matches[i] = [winneri, loseri]
 * indicates that the player winneri defeated player loseri in a match.
 *
 * Return a list answer of size 2 where:
 *
 *
 * answer[0] is a list of all players that have not lost any matches.
 * answer[1] is a list of all players that have lost exactly one match.
 *
 *
 * The values in the two lists should be returned in increasing order.
 *
 * Note:
 *
 *
 * You should only consider the players that have played at least one
 * match.
 * The testcases will be generated such that no two matches will have the same
 * outcome.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: matches =
 * [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
 * Output: [[1,2,10],[4,5,7,8]]
 * Explanation:
 * Players 1, 2, and 10 have not lost any matches.
 * Players 4, 5, 7, and 8 each have lost one match.
 * Players 3, 6, and 9 each have lost two matches.
 * Thus, answer[0] = [1,2,10] and answer[1] = [4,5,7,8].
 *
 *
 * Example 2:
 *
 *
 * Input: matches = [[2,3],[1,3],[5,4],[6,4]]
 * Output: [[1,2,5,6],[]]
 * Explanation:
 * Players 1, 2, 5, and 6 have not lost any matches.
 * Players 3 and 4 each have lost two matches.
 * Thus, answer[0] = [1,2,5,6] and answer[1] = [].
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= matches.length <= 10^5
 * matches[i].length == 2
 * 1 <= winneri, loseri <= 10^5
 * winneri != loseri
 * All matches[i] are unique.
 *
 *
 */

// @lc code=start
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
#define MAX_N 100000
int** findWinners(int** matches, int matches_num, int* matchesColSize,
                  int* returnSize, int** returnColumnSizes) {
  bool players[MAX_N + 1] = {false};
  int losses[MAX_N + 1] = {0};
  for (int i = 0; i < matches_num; ++i) {
    players[matches[i][0]] = players[matches[i][1]] = true;
    ++losses[matches[i][1]];
  }  // loop over matches
  int** ans = malloc(2 * sizeof(int*));
  ans[0] = malloc(MAX_N * sizeof(int));
  ans[1] = malloc(MAX_N * sizeof(int));

  *returnSize = 2;
  *returnColumnSizes = malloc(2 * sizeof(int));
  (*returnColumnSizes)[0] = 0;
  (*returnColumnSizes)[1] = 0;
  for (int i = 1; i <= MAX_N; ++i) {
    if (!players[i]) continue;
    const int losses_num = losses[i];
    if (losses_num < 2)
      ans[losses_num][(*returnColumnSizes)[losses_num]++] = i;
  }  // loop over all possible players
  return ans;
}
// @lc code=end
