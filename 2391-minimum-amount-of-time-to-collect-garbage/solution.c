/*
 * @lc app=leetcode id=2391 lang=c
 *
 * [2391] Minimum Amount of Time to Collect Garbage
 *
 * https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/description/
 *
 * algorithms
 * Medium (82.51%)
 * Likes:    1046
 * Dislikes: 146
 * Total Accepted:    71.9K
 * Total Submissions: 84.2K
 * Testcase Example:  '["G","P","GP","GG"]\n[2,4,3]'
 *
 * You are given a 0-indexed array of strings garbage where garbage[i]
 * represents the assortment of garbage at the i^th house. garbage[i] consists
 * only of the characters 'M', 'P' and 'G' representing one unit of metal,
 * paper and glass garbage respectively. Picking up one unit of any type of
 * garbage takes 1 minute.
 *
 * You are also given a 0-indexed integer array travel where travel[i] is the
 * number of minutes needed to go from house i to house i + 1.
 *
 * There are three garbage trucks in the city, each responsible for picking up
 * one type of garbage. Each garbage truck starts at house 0 and must visit
 * each house in order; however, they do not need to visit every house.
 *
 * Only one garbage truck may be used at any given moment. While one truck is
 * driving or picking up garbage, the other two trucks cannot do anything.
 *
 * Return the minimum number of minutes needed to pick up all the garbage.
 *
 *
 * Example 1:
 *
 *
 * Input: garbage = ["G","P","GP","GG"], travel = [2,4,3]
 * Output: 21
 * Explanation:
 * The paper garbage truck:
 * 1. Travels from house 0 to house 1
 * 2. Collects the paper garbage at house 1
 * 3. Travels from house 1 to house 2
 * 4. Collects the paper garbage at house 2
 * Altogether, it takes 8 minutes to pick up all the paper garbage.
 * The glass garbage truck:
 * 1. Collects the glass garbage at house 0
 * 2. Travels from house 0 to house 1
 * 3. Travels from house 1 to house 2
 * 4. Collects the glass garbage at house 2
 * 5. Travels from house 2 to house 3
 * 6. Collects the glass garbage at house 3
 * Altogether, it takes 13 minutes to pick up all the glass garbage.
 * Since there is no metal garbage, we do not need to consider the metal
 * garbage truck.
 * Therefore, it takes a total of 8 + 13 = 21 minutes to collect all the
 * garbage.
 *
 *
 * Example 2:
 *
 *
 * Input: garbage = ["MMM","PGM","GP"], travel = [3,10]
 * Output: 37
 * Explanation:
 * The metal garbage truck takes 7 minutes to pick up all the metal garbage.
 * The paper garbage truck takes 15 minutes to pick up all the paper garbage.
 * The glass garbage truck takes 15 minutes to pick up all the glass garbage.
 * It takes a total of 7 + 15 + 15 = 37 minutes to collect all the garbage.
 *
 *
 *
 * Constraints:
 *
 *
 * 2 <= garbage.length <= 10^5
 * garbage[i] consists of only the letters 'M', 'P', and 'G'.
 * 1 <= garbage[i].length <= 10
 * travel.length == garbage.length - 1
 * 1 <= travel[i] <= 100
 *
 *
 */

// @lc code=start
int garbageCollection(char **houses, int houses_num, int *travels,
                      int travels_num) {
  int ans = 0;
  int curr[127] = {0};
  char *house_garbage;
  ans = strlen(houses[0]);
  for (int house_idx = 1; house_idx < houses_num; ++house_idx) {
    const int travel_to_current_house = travels[house_idx - 1];
    curr['G'] += travel_to_current_house;
    curr['P'] += travel_to_current_house;
    curr['M'] += travel_to_current_house;
    house_garbage = houses[house_idx];
    const int garbage_types_num = strlen(house_garbage);
    ans += garbage_types_num;
    for (int garbage_idx = 0; garbage_idx < garbage_types_num; ++garbage_idx) {
      const char garbage_type = house_garbage[garbage_idx];
      ans += curr[garbage_type];
      curr[garbage_type] = 0;
    }   /* loop over the current house garbage types */
  }     /* loop over the houses */
  return ans;
}
// @lc code=end