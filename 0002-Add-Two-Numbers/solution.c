/**
* Definition for singly-linked list.

struct ListNode {
  int val;
  struct ListNode *next;
} ListNode;

*/

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
  struct ListNode *result = (struct ListNode *)malloc(sizeof(struct ListNode));
  result->val = 0;
  result->next = NULL;
  struct ListNode *t = result;
  int c = 0;
  while (l1 || l2 || c) {
    t->val = c;
    if (l1) {
      t->val += l1->val;
      l1 = l1->next;
    }
    if (l2) {
      t->val += l2->val;
      l2 = l2->next;
    }
    c = (t->val) / 10;
    t->val %= 10;
    if (l1 || l2 || c) {
      t->next = (struct ListNode *)malloc(sizeof(struct ListNode));
      t = t->next;
      t->val = 0;
      t->next = NULL;
    }
  }
  return result;
}