/*
 * @lc app=leetcode id=1743 lang=c
 *
 * [1743] Restore the Array From Adjacent Pairs
 */

// @lc code=start
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_NUM (100000)
#define MIN_NUM (-100000)
#define NONE (MAX_NUM + 1)
#define LUT_LEN (MAX_NUM - MIN_NUM + 2)
#define NUM2IDX(num) (num - MIN_NUM)

typedef struct {
  int val;
  int adj_vals_num;
  int adj_vals[2];
} desc_t;

int *restoreArray(int **adj_pairs, int adj_pairs_num, int *adj_pair_size,
                  int *ans_len) {
  int idx_lut[LUT_LEN];
  memset(idx_lut, 0, sizeof(idx_lut));
  desc_t descs[LUT_LEN];
  int descs_num = 0;

  // for (int i = 0; i < 10; ++i) {
  //   printf("%d ", lut[i]);
  // }
  int desc_idx;
  int lut_idx;
  int val, val2;
  for (int i = 0; i < adj_pairs_num; ++i) {
    for (int j = 0; j < 2; ++j) {
      val = adj_pairs[i][j];
      val2 = adj_pairs[i][1 - j];
      lut_idx = NUM2IDX(val);
      desc_idx = idx_lut[lut_idx];
      if (!desc_idx) {
        desc_idx = ++descs_num;
        idx_lut[lut_idx] = desc_idx;
        descs[desc_idx].val = val;
        descs[desc_idx].adj_vals_num = 0;
      }
      const int adj_val_idx = descs[desc_idx].adj_vals_num;
      ++descs[desc_idx].adj_vals_num;
      descs[desc_idx].adj_vals[adj_val_idx] = val2;
    } // loop over vals in pair
  }   // loop over pairs


  desc_idx = 1;
  for (int i = 1; i <= descs_num; ++i) {
    if (descs[i].adj_vals_num == 1) {
      desc_idx = i;
      break;
    }
  }

  *ans_len = adj_pairs_num * 2 - 2;
  int *ans = malloc((*ans_len) * sizeof(int));
  int prev_val = NONE;
  int next_val;
  int ans_idx = 0;
  for (int ans_idx = 0; ans_idx < *ans_len; ++ans_idx) {    
    ans[ans_idx] = descs[desc_idx].val;
    // printf("val=%d ", ans[ans_idx]);
    next_val = descs[desc_idx].adj_vals[0];
    if (next_val == prev_val) {
      next_val = descs[desc_idx].adj_vals[1];
    }
    lut_idx = NUM2IDX(next_val);
    desc_idx = idx_lut[lut_idx];
    // printf("next_val=%d lut_idx=%d desc_idx=%d prev_val=%d->", next_val, lut_idx, desc_idx, prev_val);
    prev_val = ans[ans_idx];
    // printf("%d\n", prev_val);
  }

  // for (int i = 0; i <= descs_num; ++i) {
  //   printf("descs[%d] = {.val=%d, .adj_vals_num=%d, .adj_vals[%d, %d]}\n", i,
  //          descs[i].val, descs[i].adj_vals_num, descs[i].adj_vals[0],
  //          descs[i].adj_vals[1]);
  // }

  return ans;
}
// @lc code=end
