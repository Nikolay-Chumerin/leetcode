/*
 * @lc app=leetcode id=872 lang=c
 *
 * [872] Leaf-Similar Trees
 *
 * https://leetcode.com/problems/leaf-similar-trees/description/
 *
 * algorithms
 * Easy (67.89%)
 * Likes:    3695
 * Dislikes: 85
 * Total Accepted:    362K
 * Total Submissions: 522.7K
 * Testcase Example:  '[3,5,1,6,2,9,8,null,null,7,4]\n' +
  '[3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]'
 *
 * Consider all the leaves of a binary tree, from left to right order, the
 * values of those leaves form a leaf value sequence.
 *
 *
 *
 * For example, in the given tree above, the leaf value sequence is (6, 7, 4,
 * 9, 8).
 *
 * Two binary trees are considered leaf-similar if their leaf value sequence is
 * the same.
 *
 * Return true if and only if the two given trees with head nodes root1 and
 * root2 are leaf-similar.
 *
 *
 * Example 1:
 *
 *
 * Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 =
 * [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
 * Output: true
 *
 *
 * Example 2:
 *
 *
 * Input: root1 = [1,2,3], root2 = [1,3,2]
 * Output: false
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in each tree will be in the range [1, 200].
 * Both of the given trees will have values in the range [0, 200].
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

#define MAX_NODES_NUM (200)

typedef struct {
  int values[MAX_NODES_NUM];
  int values_num;
} node_values_t;

void get_leaves_values(const struct TreeNode* node, node_values_t* leaves) {
  if (!node->left && !node->right) {
    leaves->values[leaves->values_num++] = node->val;
    return;
  }
  if (node->left) get_leaves_values(node->left, leaves);
  if (node->right) get_leaves_values(node->right, leaves);
}

bool leafSimilar(struct TreeNode* root1, struct TreeNode* root2) {
  node_values_t leaves1, leaves2;
  memset(&leaves1, 0, sizeof(node_values_t));
  memset(&leaves2, 0, sizeof(node_values_t));
  get_leaves_values(root1, &leaves1);
  get_leaves_values(root2, &leaves2);
  return !memcmp(&leaves1, &leaves2, sizeof(node_values_t));
}
// @lc code=end
