/*
 * @lc app=leetcode id=1026 lang=c
 *
 *    
 *
 * https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/description/
 *
 * algorithms
 * Medium (75.61%)
 * Likes:    4632
 * Dislikes: 142
 * Total Accepted:    271.5K
 * Total Submissions: 351.6K
 * Testcase Example:  '[8,3,10,1,6,null,14,null,null,4,7,13]'
 *
 * Given the root of a binary tree, find the maximum value v for which there
 * exist different nodes a and b where v = |a.val - b.val| and a is an ancestor
 * of b.
 *
 * A node a is an ancestor of b if either: any child of a is equal to b or any
 * child of a is an ancestor of b.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
 * Output: 7
 * Explanation: We have various ancestor-node differences, some of which are
 * given below :
 * |8 - 3| = 5
 * |3 - 7| = 4
 * |8 - 1| = 7
 * |10 - 13| = 3
 * Among all possible differences, the maximum value of 7 is obtained by |8 -
 * 1| = 7.
 *
 * Example 2:
 *
 *
 * Input: root = [1,null,2,null,0,3]
 * Output: 3
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [2, 5000].
 * 0 <= Node.val <= 10^5
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
typedef struct TreeNode TreeNode;
#define MAX_N (5000)
int vals[MAX_N];
int vals_num = 0;
int ans = 0;

void traverse(const TreeNode* node) {
  if (!node) return;
  const int val = node->val;
  for (int i = 0; i < vals_num; ++i) {
    const int abs_diff = abs(vals[i] - val);
    if (ans < abs_diff) ans = abs_diff;
  }
  vals[vals_num++] = val;
  traverse(node->left);
  traverse(node->right);
  --vals_num;
}

int maxAncestorDiff(const TreeNode* root) {
  ans = 0;
  vals_num = 0;
  traverse(root);
  return ans;
}  // @lc code=end
