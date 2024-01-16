/*
 * @lc app=leetcode id=380 lang=c
 *
 * [380] Insert Delete GetRandom O(1)
 *
 * https://leetcode.com/problems/insert-delete-getrandom-o1/description/
 *
 * algorithms
 * Medium (52.81%)
 * Likes:    8893
 * Dislikes: 571
 * Total Accepted:    826.9K
 * Total Submissions: 1.5M
 * Testcase Example:
 '["RandomizedSet","insert","remove","insert","getRandom","remove","insert","getRandom"]\n'
 +
  '[[],[1],[2],[2],[],[1],[2],[]]'
 *
 * Implement the RandomizedSet class:
 *
 *
 * RandomizedSet() Initializes the RandomizedSet object.
 * bool insert(int val) Inserts an item val into the set if not present.
 * Returns true if the item was not present, false otherwise.
 * bool remove(int val) Removes an item val from the set if present. Returns
 * true if the item was present, false otherwise.
 * int getRandom() Returns a random element from the current set of elements
 * (it's guaranteed that at least one element exists when this method is
 * called). Each element must have the same probability of being returned.
 *
 *
 * You must implement the functions of the class such that each function works
 * in average O(1) time complexity.
 *
 *
 * Example 1:
 *
 *
 * Input
 * ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove",
 * "insert", "getRandom"]
 * [[], [1], [2], [2], [], [1], [2], []]
 * Output
 * [null, true, false, true, 2, true, false, 2]
 *
 * Explanation
 * RandomizedSet randomizedSet = new RandomizedSet();
 * randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was
 * inserted successfully.
 * randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
 * randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now
 * contains [1,2].
 * randomizedSet.getRandom(); // getRandom() should return either 1 or 2
 * randomly.
 * randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now
 * contains [2].
 * randomizedSet.insert(2); // 2 was already in the set, so return false.
 * randomizedSet.getRandom(); // Since 2 is the only number in the set,
 * getRandom() will always return 2.
 *
 *
 *
 * Constraints:
 *
 *
 * -2^31 <= val <= 2^31 - 1
 * At most 2 * 10^5 calls will be made to insert, remove, and getRandom.
 * There will be at least one element in the data structure when getRandom is
 * called.
 *
 *
 */

// @lc code=start
#define UNIQUE_VALUES_MAX_NUM (200000)
#define HASH_TABLE_HALF_SIZE (262144)
#define HASH_TABLE_SIZE (HASH_TABLE_HALF_SIZE * 2)
#define HASH(val) (val & (HASH_TABLE_HALF_SIZE - 1))
#define END_IDX (-1)
#define MISSING_VAL_IDX (0)
#define NO_OUTPUT

typedef int val_t;
typedef int idx_t;

typedef struct {
  idx_t val_idx;  // index in the value table;
  idx_t next;     // Index of the next element of the collision list.
                  // 0 means that value is not present in the hash table,
                  // END_IDX indicates that this is the last element in the
                  // collision list. Values from HASH_TABLE_HALF_SIZE to
                  // HASH_TABLE_SIZE-1 indicate that there is collision list.
} hash_table_entry_t;

typedef struct {
  hash_table_entry_t* ht;
  val_t* vals;
  idx_t* ht_indices;
  idx_t sz;
  idx_t collisions_num;
} RandomizedSet;

RandomizedSet* randomizedSetCreate() {
  RandomizedSet* rs = malloc(sizeof(*rs));
  rs->sz = 0;
  rs->collisions_num = 0;
  rs->ht = calloc(sizeof(hash_table_entry_t), HASH_TABLE_SIZE);
  rs->vals = malloc(UNIQUE_VALUES_MAX_NUM * sizeof(val_t));
  rs->ht_indices = malloc(UNIQUE_VALUES_MAX_NUM * sizeof(idx_t));
  return rs;
}  // randomizedSetCreate()

#define VAL_IDX (rs->ht[ht_idx].val_idx)
bool randomizedSetInsert(RandomizedSet* rs, const int val) {
  idx_t ht_idx = HASH(val);
  if (MISSING_VAL_IDX == rs->ht[ht_idx].next) goto insert_new_value;

  while ((END_IDX != rs->ht[ht_idx].next) && (val != rs->vals[VAL_IDX])) {
    ht_idx = rs->ht[ht_idx].next;
  }
  if (val == rs->vals[VAL_IDX]) return false;

  // Add new value to the end of the collision list
  // link current element with a new value in the second half of the HT
  rs->ht[ht_idx].next = HASH_TABLE_HALF_SIZE + rs->collisions_num++;
  ht_idx = rs->ht[ht_idx].next;

insert_new_value:
  rs->ht[ht_idx].next = END_IDX;
  rs->ht[ht_idx].val_idx = rs->sz;
  rs->vals[rs->sz] = val;
  rs->ht_indices[rs->sz] = ht_idx;
  ++rs->sz;
  return true;
}  // randomizedSetInsert(..)

bool randomizedSetRemove(RandomizedSet* rs, const int val) {
  idx_t ht_idx = HASH(val);
  if (MISSING_VAL_IDX == rs->ht[ht_idx].next) return false;
  idx_t prev_ht_idx = END_IDX;
  while ((END_IDX != rs->ht[ht_idx].next) && (val != rs->vals[VAL_IDX])) {
    prev_ht_idx = ht_idx;
    ht_idx = rs->ht[ht_idx].next;
  }

  // ht_idx - is the index of either the last element in the collision list,
  // or the element pointing to the requested-to-remove value.
  if (val != rs->vals[VAL_IDX]) return false;

  // ht_idx - is the index of the element pointing to the requested-to-remove
  // value

  if (END_IDX == prev_ht_idx) {
    // ht_idx points to the first half of HT => copy the next one here
    const int next_ht_idx = rs->ht[ht_idx].next;
    if (END_IDX == next_ht_idx) {
      rs->ht[ht_idx].next = MISSING_VAL_IDX;
    } else {
      rs->ht[ht_idx] = rs->ht[next_ht_idx];
    }
    // ideally, here we need to move the last item from ht[] here and
    // decrease collisions_num, but for this specific task this can be skipped.
  } else {
    // ht_idx points to the second half of HT => skip it
    rs->ht[prev_ht_idx].next = rs->ht[ht_idx].next;
  }

  int val_idx = VAL_IDX;
  const int moved_val_ht_idx = rs->ht_indices[val_idx];
  --rs->sz;
  rs->vals[val_idx] = rs->vals[rs->sz];
  rs->ht_indices[val_idx] = rs->ht_indices[rs->sz];
  rs->ht[rs->ht_indices[val_idx]].val_idx = val_idx;
  return true;
}  // randomizedSetRemove(..)

val_t randomizedSetGetRandom(const RandomizedSet* rs) {
  idx_t idx = rand() % rs->sz;
  return rs->vals[idx];
}  // randomizedSetGetRandom(.)

void randomizedSetFree(RandomizedSet* rs) {
  if (!rs) return;
  rs->sz = 0;
  free(rs->ht);
  rs->ht = NULL;
  free(rs->vals);
  rs->vals = NULL;
  free(rs->ht_indices);
  rs->ht_indices = NULL;
}  // randomizedSetFree(.)

/**
 * Your RandomizedSet struct will be instantiated and called as such:
 * RandomizedSet* obj = randomizedSetCreate();
 * bool param_1 = randomizedSetInsert(obj, val);
 * bool param_2 = randomizedSetRemove(obj, val);
 * int param_3 = randomizedSetGetRandom(obj);
 * randomizedSetFree(obj);
 */
// @lc code=end
