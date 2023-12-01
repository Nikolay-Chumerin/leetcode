/*
 * @lc app=leetcode id=1561 lang=c
 *
 * [1561] Maximum Number of Coins You Can Get
 *
 * https://leetcode.com/problems/maximum-number-of-coins-you-can-get/description/
 *
 * algorithms
 * Medium (79.69%)
 * Likes:    1551
 * Dislikes: 173
 * Total Accepted:    113.9K
 * Total Submissions: 136.6K
 * Testcase Example:  '[2,4,1,2,7,8]'
 *
 * There are 3n piles of coins of varying size, you and your friends will take
 * piles of coins as follows:
 * 
 * 
 * In each step, you will choose any 3 piles of coins (not necessarily
 * consecutive).
 * Of your choice, Alice will pick the pile with the maximum number of
 * coins.
 * You will pick the next pile with the maximum number of coins.
 * Your friend Bob will pick the last pile.
 * Repeat until there are no more piles of coins.
 * 
 * 
 * Given an array of integers piles where piles[i] is the number of coins in
 * the i^th pile.
 * 
 * Return the maximum number of coins that you can have.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: piles = [2,4,1,2,7,8]
 * Output: 9
 * Explanation: Choose the triplet (2, 7, 8), Alice Pick the pile with 8 coins,
 * you the pile with 7 coins and Bob the last one.
 * Choose the triplet (1, 2, 4), Alice Pick the pile with 4 coins, you the pile
 * with 2 coins and Bob the last one.
 * The maximum number of coins which you can have are: 7 + 2 = 9.
 * On the other hand if we choose this arrangement (1, 2, 8), (2, 4, 7) you
 * only get 2 + 4 = 6 coins which is not optimal.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: piles = [2,4,5]
 * Output: 4
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: piles = [9,8,7,6,5,1,2,3,4]
 * Output: 18
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= piles.length <= 10^5
 * piles.length % 3 == 0
 * 1 <= piles[i] <= 10^4
 * 
 * 
 */

// @lc code=start
// int maxCoins(int* piles, int pilesSize) {
//   int comp(const void* a, const void* b) {
//   return *(int*) a - *(int*) b;
// }

/**************************************************************/
/* 65 ms */
#define MAX_PILES (10000)
int maxCoins(int* piles, const int n) {
  int hist[MAX_PILES + 1];
  memset(hist, 0, sizeof(hist));
  int min_pile = piles[0];
  int idx = piles[0];
  for (int i = 0; i < n; ++i) {
    const int pile = piles[i];
    ++hist[pile];
    idx = (pile > idx) ? pile : idx;
    min_pile = (pile < min_pile) ? pile : min_pile;    
  }
  
  int ans = 0;
  for (int steps_to_make = n/3; steps_to_make; --steps_to_make) {
    /* Skip to the maximal (so far) element */
    while (!hist[idx]) --idx;
    --hist[idx];

    /* Pick the next maximal (so far) element - ours */
    while (!hist[idx]) --idx;
    --hist[idx];
    ans += idx;
  }
  return ans;
}

/* 104 ms */
void my_quicksort(int *arr, const int beg, const int end) {
  if (beg >= end)
    return;
  const int pivot = arr[end];
  int i = beg;
  for (int j = beg; j < end; ++j) {
    const int aj = arr[j];
    if (aj >= pivot)
      continue;
    arr[j] = arr[i];
    arr[i++] = aj;
  }
  arr[end] = arr[i];
  arr[i] = pivot;
  my_quicksort(arr, beg, i - 1);
  my_quicksort(arr, i + 1, end);
} /* my_quicksort(...) */

int maxCoins2(int* piles, const int n) {
  my_quicksort(piles, 0, n - 1);
  int ans = 0;
  for (int i = n / 3; i < n; i += 2)
    ans += piles[i];
  return ans;
}// @lc code=end

