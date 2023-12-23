/*
 * @lc app=leetcode id=1496 lang=c
 *
 * [1496] Path Crossing
 *
 * https://leetcode.com/problems/path-crossing/description/
 *
 * algorithms
 * Easy (56.32%)
 * Likes:    1091
 * Dislikes: 30
 * Total Accepted:    96.1K
 * Total Submissions: 158.9K
 * Testcase Example:  '"NES"'
 *
 * Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing
 * moving one unit north, south, east, or west, respectively. You start at the
 * origin (0, 0) on a 2D plane and walk on the path specified by path.
 *
 * Return true if the path crosses itself at any point, that is, if at any time
 * you are on a location you have previously visited. Return false
 * otherwise.
 *
 *
 * Example 1:
 *
 *
 * Input: path = "NES"
 * Output: false
 * Explanation: Notice that the path doesn't cross any point more than once.
 *
 *
 * Example 2:
 *
 *
 * Input: path = "NESWW"
 * Output: true
 * Explanation: Notice that the path visits the origin twice.
 *
 *
 * Constraints:
 *
 *
 * 1 <= path.length <= 10^4
 * path[i] is either 'N', 'S', 'E', or 'W'.
 *
 *
 */

// @lc code=start
#define MAX_LEN (10000)
typedef struct {
  int16_t x;
  int16_t y;
} point_t;

typedef union {
  point_t p;
  uint32_t u32;
} point_u;

bool isPathCrossing(char* s) {
  point_u visited[MAX_LEN + 1];
  int dx['Z'] = {0};
  int dy['Z'] = {0};
  dy['N'] = dx['W'] = -1;
  dy['S'] = dx['E'] = +1;
  point_u curr;
  curr.p = (point_t){.x = 0, .y = 0};
  int visited_num = 1;
  visited[0] = curr;
  do {
    curr.p.x += dx[*s];
    curr.p.y += dy[*s];
    for (int i = 0; i < visited_num; ++i)
      if (visited[i].u32 == curr.u32) return true;
    visited[visited_num++].u32 = curr.u32;
  } while (*(++s));
  return false;
}  // @lc code=end
