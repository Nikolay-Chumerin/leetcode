/*
 * @lc app=leetcode id=232 lang=c
 *
 * [232] Implement Queue using Stacks
 *
 * https://leetcode.com/problems/implement-queue-using-stacks/description/
 *
 * algorithms
 * Easy (64.14%)
 * Likes:    7160
 * Dislikes: 406
 * Total Accepted:    820.5K
 * Total Submissions: 1.3M
 * Testcase Example:
 * '["MyQueue","push","push","peek","pop","empty"]\n[[],[1],[2],[],[],[]]'
 *
 * Implement a first in first out (FIFO) queue using only two stacks. The
 * implemented queue should support all the functions of a normal queue (push,
 * peek, pop, and empty).
 *
 * Implement the MyQueue class:
 *
 *
 * void push(int x) Pushes element x to the back of the queue.
 * int pop() Removes the element from the front of the queue and returns
 * it.
 * int peek() Returns the element at the front of the queue.
 * boolean empty() Returns true if the queue is empty, false otherwise.
 *
 *
 * Notes:
 *
 *
 * You must use only standard operations of a stack, which means only push to
 * top, peek/pop from top, size, and is empty operations are valid.
 * Depending on your language, the stack may not be supported natively. You may
 * simulate a stack using a list or deque (double-ended queue) as long as you
 * use only a stack's standard operations.
 *
 *
 *
 * Example 1:
 *
 *
 * Input
 * ["MyQueue", "push", "push", "peek", "pop", "empty"]
 * [[], [1], [2], [], [], []]
 * Output
 * [null, null, null, 1, 1, false]
 *
 * Explanation
 * MyQueue myQueue = new MyQueue();
 * myQueue.push(1); // queue is: [1]
 * myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
 * myQueue.peek(); // return 1
 * myQueue.pop(); // return 1, queue is [2]
 * myQueue.empty(); // return false
 *
 *
 *
 * Constraints:
 *
 *
 * 1 <= x <= 9
 * At most 100 calls will be made to push, pop, peek, and empty.
 * All the calls to pop and peek are valid.
 *
 *
 *
 * Follow-up: Can you implement the queue such that each operation is amortized
 * O(1) time complexity? In other words, performing n operations will take
 * overall O(n) time even if one of those operations may take longer.
 *
 */

// @lc code=start
#define CAPACITY (1000)
typedef int val_t;

//------------------------------------------------------------------------------
typedef struct {
  val_t data[CAPACITY];
  int sz;
} stack_t;
//--------------------------------------
stack_t* stack_create() {
  stack_t* stack = (stack_t*)malloc(sizeof(stack_t));
  stack->sz = 0;
  return stack;
}
//--------------------------------------
void stack_push(stack_t* stack, const val_t x) { stack->data[stack->sz++] = x; }
//--------------------------------------
val_t stack_pop(stack_t* stack) { return stack->data[--stack->sz]; }
//--------------------------------------
bool stack_empty(const stack_t* stack) { return (stack->sz <= 0); }
//--------------------------------------
void stack_pump(stack_t* src, stack_t* dst) {
  while (!stack_empty(src)) {
    stack_push(dst, stack_pop(src));
  }
}
//--------------------------------------
val_t stack_peek(const stack_t* stack) { return stack->data[stack->sz - 1]; }
//--------------------------------------
void stack_clear(stack_t* stack) { stack->sz = 0; }
//--------------------------------------
void stack_free(stack_t* stack) { stack->sz = 0; }
//------------------------------------------------------------------------------
typedef struct {
  stack_t* s1;
  stack_t* s2;
} MyQueue;
//--------------------------------------
MyQueue* myQueueCreate() {
  MyQueue* q = (MyQueue*)malloc(sizeof(MyQueue));
  q->s1 = stack_create();
  q->s2 = stack_create();
  return q;
}
//--------------------------------------
void myQueuePush(MyQueue* q, const val_t x) { stack_push(q->s1, x); }
//--------------------------------------
val_t myQueuePop(MyQueue* q) {
  stack_clear(q->s2);
  stack_pump(q->s1, q->s2);
  const val_t ans = stack_pop(q->s2);
  stack_pump(q->s2, q->s1);
  return ans;
}
//--------------------------------------
val_t myQueuePeek(MyQueue* q) {
  stack_clear(q->s2);
  stack_pump(q->s1, q->s2);
  const val_t ans = stack_peek(q->s2);
  stack_pump(q->s2, q->s1);
  return ans;
}
//--------------------------------------
bool myQueueEmpty(MyQueue* q) { return stack_empty(q->s1); }
//--------------------------------------
void myQueueFree(MyQueue* q) {
  stack_clear(q->s1);
  free(q->s1);
  q->s1 = NULL;
  stack_clear(q->s2);
  free(q->s2);
  q->s2 = NULL;
}
//------------------------------------------------------------------------------
/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 *' int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/
// @lc code=end
