/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
  string str_ = "";
  void traverse(const TreeNode* node) {
    str_ += to_string(node->val);
    if (!node->left && !node->right)
      return;
    str_.append(1, '(');
    if (node->left) {
      traverse(node->left);
    }
    str_.append(1, ')');
    if (node->right) {
      str_.append(1, '(');
      traverse(node->right);
      str_.append(1, ')');
    } /* if (node->right) */
  }

public:
    string tree2str(const TreeNode* root) {
      traverse(root);
      return str_;
    }
};
