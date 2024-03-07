/*
 * @lc app=leetcode id=948 lang=c
 *
 * [948] Bag of Tokens
 *
 * https://leetcode.com/problems/bag-of-tokens/description/
 *
 * algorithms
 * Medium (52.24%)
 * Likes:    2968
 * Dislikes: 507
 * Total Accepted:    189.1K
 * Total Submissions: 326.8K
 * Testcase Example:  '[100]\n50'
 *
 * You start with an initial power of power, an initial score of 0, and a bag
 * of tokens given as an integer array tokens, where each tokens[i] donates the
 * value of tokeni.
 * 
 * Your goal is to maximize the total score by strategically playing these
 * tokens. In one move, you can play an unplayed token in one of the two ways
 * (but not both for the same token):
 * 
 * 
 * Face-up: If your current power is at least tokens[i], you may play tokeni,
 * losing tokens[i] power and gaining 1 score.
 * Face-down: If your current score is at least 1, you may play tokeni, gaining
 * tokens[i] power and losing 1 score.
 * 
 * 
 * Return the maximum possible score you can achieve after playing any number
 * of tokens.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: tokens = [100], power = 50
 * 
 * Output: 0
 * 
 * Explanation: Since your score is 0 initially, you cannot play the token
 * face-down. You also cannot play it face-up since your power (50) is less
 * than tokens[0] (100).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: tokens = [200,100], power = 150
 * 
 * Output: 1
 * 
 * Explanation: Play token1 (100) face-up, reducing your power to 50 and
 * increasing your score to 1.
 * 
 * There is no need to play token0, since you cannot play it face-up to add to
 * your score. The maximum score achievable is 1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: tokens = [100,200,300,400], power = 200
 * 
 * Output: 2
 * 
 * Explanation: Play the tokens in this order to get a score of 2:
 * 
 * 
 * Play token0 (100) face-up, reducing power to 100 and increasing score to
 * 1.
 * Play token3 (400) face-down, increasing power to 500 and reducing score to
 * 0.
 * Play token1 (200) face-up, reducing power to 300 and increasing score to
 * 1.
 * Play token2 (300) face-up, reducing power to 0 and increasing score to 2.
 * 
 * 
 * The maximum score achievable is 2.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= tokens.length <= 1000
 * 0 <= tokens[i], power < 10^4
 * 
 * 
 */

// @lc code=start
int comp(const void* a, const void* b) {
  return *(int*) a - *(int*) b;
}

int bagOfTokensScore(int* tokens, int tokens_num, int power) {
  int score = 0;
  qsort(tokens, tokens_num, sizeof(int), comp);
  int l = 0;
  int r = tokens_num - 1;
  while ((l < r) && (score >= 0) && (power >= 0)) {
    if (tokens[l] <= power) {
      ++score;
      power -= tokens[l++];
    } else {
      --score;
      power += tokens[r--];
    }
  }
  score += (tokens_num > 0) && (l <= tokens_num) && (tokens[l] <= power);
  return score;
}
// @lc code=end

