/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

typedef struct ListNode* node_t;
node_t middleNode(node_t head) {
  node_t fast = head;
  do {
    if (NULL == fast || NULL == fast->next) return head;
    fast = fast->next->next;
    head = head->next;
  } while (true);
}
