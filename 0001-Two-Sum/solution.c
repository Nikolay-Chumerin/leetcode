#define HASH_TABLE_HALF_SIZE (8192)
#define HASH_TABLE_SIZE (HASH_TABLE_HALF_SIZE * 2)
#define HASH(val) (val & (HASH_TABLE_HALF_SIZE - 1))
#define END_IDX (-1)

typedef struct {
  int val;        /* Value from nums[] array. */
  short idx;      /* Index of that value. */
  short next_idx; /* Index of the next element of the collision list.
                     0 means that value is not present in the hash table,
                     END_IDX indicates that this is the last element in the
                     collision list. Values from HASH_TABLE_HALF_SIZE to
                     HASH_TABLE_SIZE-1 indicate that there is collision list. */
} ht_t;

int *twoSum(int *nums, const int n, const int target, int *ans_len) {
  ht_t ht[HASH_TABLE_SIZE]; /* Hash table implemented as array. */
  /* The hist half of the ht[] (with indices from 0 to HASH_MOD-1)
   would be the actual hash table, while the second/remaining half is
   reserved for collisions. */
  memset(ht, 0, sizeof(ht)); /* Initially, hash table is empty. */
  int *ans = malloc(2 * sizeof(int));
  *ans_len = 2;
  int collisions_num = 0;
  int idx;
  for (int i = 0; i < n; ++i) {
    ans[0] = i;
    const int num = nums[i];
    const int rest = target - num;
    const int rest_hash_idx = HASH(rest);
    if (ht[rest_hash_idx].next_idx) {
      /* Potentially found... let's check the collisions (if any)... */
      idx = rest_hash_idx;
      do {
        if (ht[idx].val == rest) {
          ans[1] = ht[idx].idx;
          return ans;
        }
        idx = ht[idx].next_idx;
      } while (idx != END_IDX); /* loop over collision list */
    } /* "found a candidate for the `rest` value in the hash table" branch */
    /* add num to hash table */
    const int num_hash_idx = HASH(num);
    if (ht[num_hash_idx].next_idx) {
      /* Collision detected. Append to num to the existing collision list. */
      idx = HASH_TABLE_HALF_SIZE + collisions_num++;
      ht[idx].next_idx = ht[num_hash_idx].next_idx;
      ht[num_hash_idx].next_idx = idx;
    } else {
      /* Value `num` was not in the hash table => Add it there. */
      idx = num_hash_idx;
      ht[idx].next_idx = END_IDX; /* No collisions for new element. */
    }
    /* The `val` and `idx` fields need to filled for both cases (new/append). */
    ht[idx].val = num;
    ht[idx].idx = i;
  } /* loop over nums[] */
  return ans;
} /* int *twoSum(int *nums, const int n, const int target, int *ans_len) */

/******************************************************************************/
int *twoSum_slow(int *nums, int numsSize, int target, int *returnSize) {
  int *result = (int *)malloc(2 * sizeof(int));
  *returnSize = 2;
  for (int i = 1; i < numsSize; ++i) {
    for (int j = 0; j < i; ++j) {
      if (nums[i] == target - nums[j]) {
        result[0] = j;
        result[1] = i;
        goto exit;
      }
    } // j-loop
  }   // i-loop
exit:
  return result;
}
