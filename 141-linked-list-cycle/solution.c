/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode list_node_t;

bool hasCycle(list_node_t *head) {
  if (!head || !head->next) return false;
  list_node_t *fast = head, *slow = head;
  do {
    fast = fast ? fast->next : NULL;
    fast = fast ? fast->next : NULL;
    slow = slow ? slow->next : NULL;
  } while (slow != fast);
  return slow;
}