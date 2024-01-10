/*
 * @lc app=leetcode id=2385 lang=c
 *
 * [2385] Amount of Time for Binary Tree to Be Infected
 *
 * https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/description/
 *
 * algorithms
 * Medium (58.58%)
 * Likes:    2079
 * Dislikes: 44
 * Total Accepted:    75.7K
 * Total Submissions: 123.1K
 * Testcase Example:  '[1,5,3,null,4,10,6,9,2]\n3'
 *
 * You are given the root of a binary tree with unique values, and an integer
 * start. At minute 0, an infection starts from the node with value start.
 *
 * Each minute, a node becomes infected if:
 *
 *
 * The node is currently uninfected.
 * The node is adjacent to an infected node.
 *
 *
 * Return the number of minutes needed for the entire tree to be infected.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [1,5,3,null,4,10,6,9,2], start = 3
 * Output: 4
 * Explanation: The following nodes are infected during:
 * - Minute 0: Node 3
 * - Minute 1: Nodes 1, 10 and 6
 * - Minute 2: Node 5
 * - Minute 3: Node 4
 * - Minute 4: Nodes 9 and 2
 * It takes 4 minutes for the whole tree to be infected so we return 4.
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1], start = 1
 * Output: 0
 * Explanation: At minute 0, the only node in the tree is infected so we return
 * 0.
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 10^5].
 * 1 <= Node.val <= 10^5
 * Each node has a unique value.
 * A node with a value of start exists in the tree.
 *
 *
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 * };
 */

#define MAX_N (100000)
typedef struct {
  int step;
  int indices[3];  // [0] - father, [1] - left son, [2] - right son
} node_info_t;

#define father_idx indices[0]
#define left_son_idx indices[1]
#define right_son_idx indices[2]

typedef struct TreeNode TreeNode;

node_info_t nodes[MAX_N + 1];
int nodes_num = 0;

void populate_nodes_array(const TreeNode* node) {
  ++nodes_num;
  if (node->left) {
    nodes[node->left->val].father_idx = node->val;
    nodes[node->val].left_son_idx = node->left->val;
    populate_nodes_array(node->left);
  }
  if (node->right) {
    nodes[node->right->val].father_idx = node->val;
    nodes[node->val].right_son_idx = node->right->val;
    populate_nodes_array(node->right);
  }
}  // populate_nodes_array(.)

int amountOfTime(const TreeNode* root, const int start) {
  memset(nodes, 0, sizeof(nodes));
  nodes_num = 0;
  populate_nodes_array(root);
  int clean_nodes_num = nodes_num - 1;
  if (!clean_nodes_num) return 0;
  nodes[start].step = 1;
  int step = 0;

  int node_indices[2][MAX_N];
  memset(node_indices, 0, sizeof(node_indices));
  int src_row = 0, dst_row = 0;
  node_indices[src_row][0] = start;
  int src_nodes_num = 1, dst_nodes_num = 0;

  do {
    ++step;
    dst_row = 1 - src_row;
    dst_nodes_num = 0;
    for (int i = 0; i < src_nodes_num; ++i) {
      const int src_node_idx = node_indices[src_row][i];
      for (int j = 0; j < 3; ++j) {
        const int relative_node_idx = nodes[src_node_idx].indices[j];
        if (relative_node_idx && !nodes[relative_node_idx].step) {
          --clean_nodes_num;
          nodes[relative_node_idx].step = step;
          node_indices[dst_row][dst_nodes_num] = relative_node_idx;
          ++dst_nodes_num;
        }  // found "clean" relative branch
      }    // loop over current node's relatives
    }      // loop over src nodes
    src_nodes_num = dst_nodes_num;
    src_row = 1 - src_row;    // swap src <-> dst rows of node_indices[][] array
  } while (clean_nodes_num);  // main loop

  return step;
}
// @lc code=end
