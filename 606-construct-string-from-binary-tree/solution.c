/*
 * @lc app=leetcode id=606 lang=c
 *
 * [606] Construct String from Binary Tree
 *
 * https://leetcode.com/problems/construct-string-from-binary-tree/description/
 *
 * algorithms
 * Easy (64.80%)
 * Likes:    2994
 * Dislikes: 3474
 * Total Accepted:    266.5K
 * Total Submissions: 398K
 * Testcase Example:  '[1,2,3,4]'
 *
 * Given the root of a binary tree, construct a string consisting of
 * parenthesis and integers from a binary tree with the preorder traversal way,
 * and return it.
 *
 * Omit all the empty parenthesis pairs that do not affect the one-to-one
 * mapping relationship between the string and the original binary tree.
 *
 *
 * Example 1:
 *
 *
 * Input: root = [1,2,3,4]
 * Output: "1(2(4))(3)"
 * Explanation: Originally, it needs to be "1(2(4)())(3()())", but you need to
 * omit all the unnecessary empty parenthesis pairs. And it will be
 * "1(2(4))(3)"
 *
 *
 * Example 2:
 *
 *
 * Input: root = [1,2,3,null,4]
 * Output: "1(2()(4))(3)"
 * Explanation: Almost the same as the first example, except we cannot omit the
 * first parenthesis pair to break the one-to-one mapping relationship between
 * the input and the output.
 *
 *
 *
 * Constraints:
 *
 *
 * The number of nodes in the tree is in the range [1, 10^4].
 * -1000 <= Node.val <= 1000
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

#define NODES_MAX_NUM (10000)

int print_int(char *s, int a) {
  int n = 0; /* number of chars added to the string */

  if (a < 0) {
    s[n++] = '-';
    a = -a;
  }

  int d = (a >= 1000) ? 1000 : (a >= 100) ? 100 : (a >= 10) ? 10 : 1;
  while (d) {
    s[n++] = '0' + (a / d);
    a %= d;
    d /= 10;
  }
  return n;
} /* int print_int(..) */

void traverse(struct TreeNode *node, char *ans, int *ans_idx) {
  (*ans_idx) += print_int(ans + (*ans_idx), node->val);
  const bool node_has_kids = node->left || node->right;

  if (node_has_kids) {
    ans[*ans_idx] = '(';
    ++(*ans_idx);
  } /* if (node_has_kids) */

  if (node->left) {
    traverse(node->left, ans, ans_idx);
  } /* if (node->left) */

  if (node_has_kids) {

    ans[*ans_idx] = ')';
    ++(*ans_idx);

    if (node->right) {
      ans[*ans_idx] = '(';
      ++(*ans_idx);
      traverse(node->right, ans, ans_idx);
      ans[*ans_idx] = ')';
      ++(*ans_idx);
    } /* if (node->right) */

  } /* if (node_has_kids) */
}

char *tree2str(struct TreeNode *root) {
  char *ans = calloc(NODES_MAX_NUM * 3 * 5, sizeof(char));
  int ans_idx = 0;
  traverse(root, ans, &ans_idx);
  return ans;
}
// @lc code=end
