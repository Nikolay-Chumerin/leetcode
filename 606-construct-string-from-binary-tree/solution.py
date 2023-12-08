# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def tree2str(self, node: Optional[TreeNode]) -> str:
        ans = str(node.val)
        if node.left or node.right:
            ans += f"({self.tree2str(node.left)})" if node.left else "()"
            ans += f"({self.tree2str(node.right)})" if node.right else ""
        return ans
