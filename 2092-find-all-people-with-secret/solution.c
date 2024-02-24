/*
 * @lc app=leetcode id=2092 lang=c
 *
 * [2092] Find All People With Secret
 *
 * https://leetcode.com/problems/find-all-people-with-secret/description/
 *
 * algorithms
 * Hard (34.23%)
 * Likes:    1339
 * Dislikes: 65
 * Total Accepted:    71.8K
 * Total Submissions: 161.5K
 * Testcase Example:  '6\n[[1,2,5],[2,3,8],[1,5,10]]\n1'
 *
 * You are given an integer n indicating there are n people numbered from 0 to
 * n - 1. You are also given a 0-indexed 2D integer array meetings where
 * meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a
 * meeting at timei. A person may attend multiple meetings at the same time.
 * Finally, you are given an integer firstPerson.
 *
 * Person 0 has a secret and initially shares the secret with a person
 * firstPerson at time 0. This secret is then shared every time a meeting takes
 * place with a person that has the secret. More formally, for every meeting,
 * if a person xi has the secret at timei, then they will share the secret with
 * person yi, and vice versa.
 *
 * The secrets are shared instantaneously. That is, a person may receive the
 * secret and share it with people in other meetings within the same time
 * frame.
 *
 * Return a list of all the people that have the secret after all the meetings
 * have taken place. You may return the answer in any order.
 *
 *
 * Example 1:
 *
 *
 * Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
 * Output: [0,1,2,3,5]
 * Explanation:
 * At time 0, person 0 shares the secret with person 1.
 * At time 5, person 1 shares the secret with person 2.
 * At time 8, person 2 shares the secret with person 3.
 * At time 10, person 1 shares the secret with person 5.​​​​
 * Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.
 *
 *
 * Example 2:
 *
 *
 * Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
 * Output: [0,1,3]
 * Explanation:
 * At time 0, person 0 shares the secret with person 3.
 * At time 2, neither person 1 nor person 2 know the secret.
 * At time 3, person 3 shares the secret with person 0 and person 1.
 * Thus, people 0, 1, and 3 know the secret after all the meetings.
 *
 *
 * Example 3:
 *
 *
 * Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
 * Output: [0,1,2,3,4]
 * Explanation:
 * At time 0, person 0 shares the secret with person 1.
 * At time 1, person 1 shares the secret with person 2, and person 2 shares the
 * secret with person 3.
 * Note that person 2 can share the secret at the same time as receiving it.
 * At time 2, person 3 shares the secret with person 4.
 * Thus, people 0, 1, 2, 3, and 4 know the secret after all the meetings.
 *
 *
 *
 * Constraints:
 *
 *
 * 2 <= n <= 10^5
 * 1 <= meetings.length <= 10^5
 * meetings[i].length == 3
 * 0 <= xi, yi <= n - 1
 * xi != yi
 * 1 <= timei <= 10^5
 * 1 <= firstPerson <= n - 1
 *
 *
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define N (100000)
bool set[N + 1];

void print_meetings(int** meetings, const int meetings_num) {
  printf("meetings_num=%d --------------------\n", meetings_num);
  for (int i = 0; i < meetings_num; ++i) {
    printf("meeting %03d: [%d, %d, %d]\n", i, meetings[i][0], meetings[i][1],
           meetings[i][2]);
  }
}

int compare_meetings(const void* a, const void* b) {
  return (*(int**)a)[2] - (*(int**)b)[2];
}

int* findAllPeople(const int n, int** meetings, const int meetings_num,
                   const int* meetingsColSize, const int first_person,
                   int* ans_len) {
  memset(set, false, sizeof(set));
  int* ans = malloc(N * sizeof(int));
  int ans_num = 0;
  qsort(meetings, meetings_num, sizeof(int*), compare_meetings);
  set[0] = true;
  set[first_person] = true;
  int i0 = 0;
  int curr_mtg_time = meetings[0][2];
  int i1 = 0;
  for (int i = 0; i < meetings_num; ++i) {
    const int t = meetings[i][2];
    if (curr_mtg_time == t) continue;
    curr_mtg_time = t;
    i1 = i;
    for (int k = 0; k <= (i1 - i0); ++k) {
      int added_num = 0;
      for (int j = i0; j < i1; ++j) {
        const int p1 = meetings[j][0];
        const int p2 = meetings[j][1];
        const bool one_knows = (set[p1] ^ set[p2]);
        added_num += one_knows;
        if (one_knows) {
          set[p1] = set[p2] = true;
        }
      }  // j
      if (0 == added_num) break;
    }  // k
    i0 = i;
  }  // i

  i1 = meetings_num;
  for (int k = 0; k <= (i1 - i0); ++k) {
    int added_num = 0;
    for (int j = i0; j < i1; ++j) {
      const int p1 = meetings[j][0];
      const int p2 = meetings[j][1];
      const bool one_knows = (set[p1] ^ set[p2]);
      added_num += one_knows;
      if (one_knows) {
        set[p1] = set[p2] = true;
      }
    }  // j
    if (0 == added_num) break;
  }  // k

  for (int i = 0; i <= N; ++i) {
    if (!set[i]) continue;
    ans[ans_num++] = i;
  }
  (*ans_len) = ans_num;
  return ans;
}
// @lc code=end
