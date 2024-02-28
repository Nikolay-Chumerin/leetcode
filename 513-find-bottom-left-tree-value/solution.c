/*
 * @lc app=leetcode id=513 lang=c
 *
 * [513] Find Bottom Left Tree Value
 *
 * https://leetcode.com/problems/find-bottom-left-tree-value/description/
 *
 * algorithms
 * Medium (67.74%)
 * Likes:    3578
 * Dislikes: 280
 * Total Accepted:    303.1K
 * Total Submissions: 433.6K
 * Testcase Example:  '[2,1,3]'
 *
 * Given the root of a binary tree, return the leftmost value in the last row
 * of the tree.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [2,1,3]
 * Output: 1
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,2,3,4,null,5,6,null,null,7]
 * Output: 7
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 10^4].
 * -2^31 <= Node.val <= 2^31 - 1
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
typedef struct TreeNode tree_node_t;
int ans;
int ans_level;
void dfs(const tree_node_t* const node, int level) {
  if (level > ans_level) {
    ans_level = level;
    ans = node->val;
  }
  ++level;
  if (node->left) dfs(node->left, level);
  if (node->right) dfs(node->right, level);
}

int findBottomLeftValue(tree_node_t* root) {
  ans = root->val;
  ans_level = 0;
  dfs(root, 0);
  return ans;
}
// @lc code=end
