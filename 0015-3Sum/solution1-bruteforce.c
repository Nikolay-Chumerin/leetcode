/**
 * Return an array of arrays of size *res_size.
 * The sizes of the arrays are returned as *res_col_sizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */

int **threeSum(int *nums, int numsSize, int *res_size, int **res_col_sizes) {
  *res_size = 0;
  int **res = NULL;

#define MAX_NUM 100000
#define COUNTS_ARRAY_SIZE (MAX_NUM * 2 + 1)
  int min_num = MAX_NUM + 1;
  int max_num = -MAX_NUM - 1;

  int counts[COUNTS_ARRAY_SIZE] = {0}; // automatically filled with zeroes

  // sort nums using counting
  int *p = nums;
  for (int i = 0; i < numsSize; ++i) {
    const int num = *p++;
    if (num < min_num)
      min_num = num;
    if (num > max_num)
      max_num = num;
    ++counts[num + MAX_NUM];
  }

  p = nums;
  int newNumsSize = 0;
  for (int i = min_num; i <= max_num; ++i) {
    int count = counts[i + MAX_NUM];
    if (!count)
      continue;
    if (count > 2) {
      count = 2 + (i == 0);
    }
    for (int j = 0; j < count; ++j, ++newNumsSize)
      *p++ = i;
  }

  numsSize = newNumsSize;
  if (numsSize < 3)
    return res;

  min_num = nums[0];
  max_num = nums[numsSize - 1];

  int res_capacity = 16384 * 4;
  int triplets_num = 0;

  res = (int **)malloc(res_capacity * sizeof(int *));
  uint64_t *hashes = (uint64_t *)malloc(res_capacity * sizeof(uint64_t));
  int *col_sizes = (int *)malloc(res_capacity * sizeof(int));

  // main loops
  for (int i = 0; i < numsSize - 2; ++i) {
    const int ni = nums[i];
    if (ni + nums[i + 1] + nums[i + 2] > 0)
      break;
    for (int j = i + 1; j < numsSize - 1; ++j) {
      const int nj = nums[j];
      if (ni + nj + nums[j + 1] > 0)
        break;
      if (ni + nj + max_num < 0)
        continue;
      const int remaining_part = -ni - nj;
      // binary search
      int min_idx = j + 1;
      int max_idx = numsSize - 1;
      while (min_idx < max_idx - 1) {
        const int mid_idx = (min_idx + max_idx) / 2;
        const int nm = nums[mid_idx];
        if (nm == remaining_part) {
          min_idx = max_idx = mid_idx;
          break;
        } else if (nm > remaining_part) {
          max_idx = mid_idx;
        } else {
          min_idx = mid_idx;
        }
      } // binary search loop

      int k;
      if (nums[min_idx] == remaining_part) {
        k = min_idx;
      } else if (nums[max_idx] == remaining_part) {
        k = max_idx;
      } else
        continue;
      const int nk = nums[k];

      // compute hash of the (ni, nj, nk) triplet
      uint64_t hash = ((uint64_t)(ni & 0x0FFFFF));
      hash |= (((uint64_t)(nj & 0x0FFFFF)) << 20);
      hash |= (((uint64_t)(nk & 0x0FFFFF)) << 40);

      // check if the triplet is unique (has not been already found before)
      bool unique = true;
      for (int l = triplets_num - 1; unique && l >= 0; --l)
        unique = hashes[l] != hash;
      if (!unique)
        continue;

      // make new triplet
      int *triplet = malloc(3 * sizeof(int));
      triplet[0] = ni;
      triplet[1] = nj;
      triplet[2] = nk;

      // resize array if needed
      if (triplets_num >= res_capacity) {
        res_capacity *= 2;
        res = (int **)realloc(res, res_capacity * sizeof(int *));
        col_sizes = (int *)realloc(col_sizes, res_capacity * sizeof(int));
        hashes = (uint64_t *)realloc(hashes, res_capacity * sizeof(uint64_t));
      }

      // append new triplet to result
      res[triplets_num] = triplet;
      col_sizes[triplets_num] = 3;
      hashes[triplets_num] = hash;
      ++triplets_num;
    } // j-loop
  }   // i-loop

  free(hashes);

  // set output
  *res_size = triplets_num;
  *res_col_sizes = col_sizes;
  return res;
}