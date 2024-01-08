/*
 * @lc app=leetcode id=938 lang=c
 *
 * [938] Range Sum of BST
 *
 * https://leetcode.com/problems/range-sum-of-bst/description/
 *
 * algorithms
 * Easy (85.93%)
 * Likes:    6590
 * Dislikes: 364
 * Total Accepted:    924.1K
 * Total Submissions: 1.1M
 * Testcase Example:  '[10,5,15,3,7,null,18]\n7\n15'
 *
 * Given the root node of a binary search tree and two integers low and high,
 * return the sum of values of all nodes with a value in the inclusive range
 * [low, high].
 *
 *
 * Example 1:
 *
 *
 * Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
 * Output: 32
 * Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 =
 * 32.
 *
 *
 * Example 2:
 *
 *
 * Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
 * Output: 23
 * Explanation: Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 =
 * 23.
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 2 * 10^4].
 * 1 <= Node.val <= 10^5
 * 1 <= low <= high <= 10^5
 * All Node.val are unique.
 *
 *
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int rangeSumBST(struct TreeNode* node, const int low, const int high) {
  if (node->val < low) {
    /* all the left branch values are too low => check the right branch only */
    return node->right ? rangeSumBST(node->right, low, high) : 0;
  } else if (node->val > high) {
    /* all the right branch values are too high => check the the branch only */
    return node->left ? rangeSumBST(node->left, low, high) : 0;
  }

  /* Remaining case: node->val is in the resired range =>
  both branches need to be checked/traversed (if they exist). */
  return node->val + (node->right ? rangeSumBST(node->right, low, high) : 0) +
         (node->left ? rangeSumBST(node->left, low, high) : 0);
}  // @lc code=end
