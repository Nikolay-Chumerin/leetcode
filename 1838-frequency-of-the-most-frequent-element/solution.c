/*
 * @lc app=leetcode id=1838 lang=c
 *
 * [1838] Frequency of the Most Frequent Element
 *
 * https://leetcode.com/problems/frequency-of-the-most-frequent-element/description/
 *
 * algorithms
 * Medium (40.18%)
 * Likes:    3456
 * Dislikes: 109
 * Total Accepted:    77.8K
 * Total Submissions: 181.1K
 * Testcase Example:  '[1,2,4]\n5'
 *
 * The frequency of an element is the number of times it occurs in an array.
 * 
 * You are given an integer array nums and an integer k. In one operation, you
 * can choose an index of nums and increment the element at that index by 1.
 * 
 * Return the maximum possible frequency of an element after performing at most
 * k operations.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,4], k = 5
 * Output: 3
 * Explanation: Increment the first element three times and the second element
 * two times to make nums = [4,4,4].
 * 4 has a frequency of 3.
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,4,8,13], k = 5
 * Output: 2
 * Explanation: There are multiple optimal solutions:
 * - Increment the first element three times to make nums = [4,4,8,13]. 4 has a
 * frequency of 2.
 * - Increment the second element four times to make nums = [1,8,8,13]. 8 has a
 * frequency of 2.
 * - Increment the third element five times to make nums = [1,4,13,13]. 13 has
 * a frequency of 2.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [3,9,6], k = 2
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^5
 * 1 <= k <= 10^5
 * 
 * 
 */

// @lc code=start
void quicksort(int *arr, const int beg, const int end) {
  if (beg >= end) return;
  const int pivot = arr[end];
  int i = beg;
  for (int j = beg; j < end; ++j) {
    const int aj = arr[j];
    if (aj >= pivot) continue;
    arr[j] = arr[i];
    arr[i++] = aj;
  }
  arr[end] = arr[i];
  arr[i] = pivot;
  quicksort(arr, beg, i - 1);
  quicksort(arr, i + 1, end);
}  /* quicksort(...) */

int maxFrequency(int* nums, const int n, const int k) {
  quicksort(nums, 0, n - 1);
  int ans = 1;
  int l = 0;
  int r = 0;
  long int sum = 0;
  while (r < n) {
    sum += nums[r++];
    while (sum > k) {
      sum -= nums[l++];
    }
    int win_len  = r - l + 1;
    if (ans < win_len) ans = win_len;
  }
  return ans;
}

/* Runtime 581 */
#define MAX_NUM (100000)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int maxFrequency2(int* nums, const int n, const int k) {
  int counts[MAX_NUM + 1];
  memset(counts, 0, sizeof(counts));
  int unique_nums[MAX_NUM + 1];
  int unique_nums_num = 0;
  for (int i = 0; i < n; ++i) {
    ++counts[nums[i]];
  }

  for (int i = 0; i <= MAX_NUM; ++i) {
    if (counts[i]) {
      unique_nums[unique_nums_num++] = i; 
    }
  }

  int ans = counts[unique_nums[0]];
  for (int i = 1; i < unique_nums_num; ++i) {
    const int unique_num = unique_nums[i];
    int new_ans = counts[unique_num];
    int j = i;
    int kk = k;
    while (--j >= 0) {
      const int uj = unique_nums[j];
      const int d = unique_num - uj;
      if (kk < d) break;
      const int potential_upgrades_num = kk / d;
      const int upgrades_num = MIN(potential_upgrades_num, counts[uj]);
      new_ans += upgrades_num;
      kk -= upgrades_num * d;
    }  /* loop over possible upgrades */
    ans = MAX(ans, new_ans);
  }  /* loop over unique nums */
  return ans;
}
// @lc code=end

