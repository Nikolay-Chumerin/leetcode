/*
 * @lc app=leetcode id=1980 lang=c
 *
 * [1980] Find Unique Binary String
 *
 * https://leetcode.com/problems/find-unique-binary-string/description/
 *
 * algorithms
 * Medium (66.57%)
 * Likes:    1585
 * Dislikes: 59
 * Total Accepted:    91.1K
 * Total Submissions: 125.3K
 * Testcase Example:  '["01","10"]'
 *
 * Given an array of strings nums containing n unique binary strings each of
 * length n, return a binary string of length n that does not appear in nums.
 * If there are multiple answers, you may return any of them.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = ["01","10"]
 * Output: "11"
 * Explanation: "11" does not appear in nums. "00" would also be correct.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = ["00","01"]
 * Output: "11"
 * Explanation: "11" does not appear in nums. "10" would also be correct.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = ["111","011","001"]
 * Output: "101"
 * Explanation: "101" does not appear in nums. "000", "010", "100", and "110"
 * would also be correct.
 * 
 * Constraints:
 * n == nums.length
 * 1 <= n <= 16
 * nums[i].length == n
 * nums[i] is either '0' or '1'.
 * All the strings of nums are unique.
 * 
 * 
 *
# Intuition
First thought was to build a set of numbers using a fixed array (16bit-element set can be implemented using an array of just $2^{16}=65536$ elements). Then scan this array for a gap. Working, but not optimal solution.

Next idea was to deploy the approach used for proving that the real numbers set $\mathbb{R}$ is uncountable (a.k.a. [Cantor's diagonal argument](https://en.wikipedia.org/wiki/Cantor%27s_diagonal_argument)).

# Approach
To construct an element $m$, which would not be present in the provided set (array) `arr[]` let's use the Cantor's anti-diagonal approach and define $m_i$ (the $i^{\text th}$ bit of $m$) as an inverse of the $i^{\text th}$ bit of the `arr[i]`.

E.g., if the input array `arr[]` looks as follows:
`arr[0]` = "$\red 0000000\dots$"
`arr[1]` = "$1\red100101\dots$"
`arr[2]` = "$01\red00110\dots$"
`arr[3]` = "$011\red1001\dots$"
`arr[4]` = "$1010\red010\dots$"
...
then the desired element $m$ is constructed as:
$m=$ "$\green{100101}\dots$", $i^{\text th}$ bit-character of which (shown in green) corresponds to the inverse (two-complement) of the corresponding $i^{\text th}$ bit-character (shown in red of) `arr[i]`. The bit-character inversion ('0' <-> '1') can be implemented without branching (`if` or ternary operators in C-like languages) via flipping the last bit of the `arr[i]` character's code, which in turn is can be done via `& 1` (`xor 1`).

As we don't need to allocate memory for the result (it is not mentioned in the problem description), we can re-use the first element `arr[0]` of the input array `arr`.

# Complexity
- Time complexity: $$O(n)$$.
- Space complexity: $$O(1)$$.

 */

// @lc code=start
char* findDifferentBinaryString(char** nums, const int n) {
  for (int i = 0; i < n && nums[0][i]; ++i)
    nums[0][i] = nums[i][i] ^ 1; /* Flip the last bit */
  return nums[0];    
}
// @lc code=end

