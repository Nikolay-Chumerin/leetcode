/* Solution 2:
 */

int comp(const void *x, const void *y) { return *(int *)x - *(int *)y; }

int **threeSum(int *nums, int numsSize, int *res_size, int **res_col_sizes) {
  *res_size = 0;
  int **res = NULL;
  if (numsSize < 3)
    return res;

  // sort nums
  qsort(nums, numsSize, sizeof(int), comp);

  // allow only 2 non-zero duplicates and zero is allowed to appear 3 times
  int newNumsSize = 1;
  int *pn = &nums[1];
  int c = 1;
  for (int i = 1; i < numsSize; ++i) {
    if (nums[i] != nums[i - 1]) {
      c = 1;
    } else {
      ++c;
    }
    if (((nums[i] == 0) && (c <= 3)) || (c <= 2)) {
      *pn++ = nums[i];
      ++newNumsSize;
    }
  } // i-loop

  numsSize = newNumsSize;

  int res_capacity = 32;
  int triplets_num = 0;

  res = (int **)malloc(res_capacity * sizeof(int *));
  int *col_sizes = (int *)malloc(res_capacity * sizeof(int));

  // main loops
  for (int i = 0; i < numsSize - 2; ++i) {
    const int ni = nums[i];
    if (ni > 0)
      break;
    int l = i + 1;
    int r = numsSize - 1;
    while (l < r) {
      const int nl = nums[l];
      const int nr = nums[r];
      const int sum = ni + nl + nr;
      if (sum < 0) {
        // increase sum by moving left index (l) forward
        ++l;
      } else if (sum > 0) {
        // decrease sum by moving right index (r) backward
        --r;
      } else {
        for (int i = 1; i <= triplets_num && res[triplets_num - i][0] == ni;
             ++i) {
          if ((res[triplets_num - i][1] == nl) &&
              (res[triplets_num - i][2] == nr))
            goto lr_loop_exit;
        }

        // Create a triplet
        int *triplet = malloc(3 * sizeof(int));
        triplet[0] = ni;
        triplet[1] = nl;
        triplet[2] = nr;

        // resize array if needed
        if (triplets_num >= res_capacity) {
          res_capacity *= 32;
          res = (int **)realloc(res, res_capacity * sizeof(int *));
          col_sizes = (int *)realloc(col_sizes, res_capacity * sizeof(int));
        }

        // append new triplet to result
        res[triplets_num] = triplet;
        col_sizes[triplets_num] = 3;
        ++triplets_num;
      lr_loop_exit:
        ++l;

        // skip the same values from the left and right sides
        while ((l < r) && (nums[l] == nl))
          ++l;
        while ((l < r) && (nums[r] == nr))
          --r;
      }
    } // l/r-loop
  }   // i-loop

  // set output
  *res_size = triplets_num;
  *res_col_sizes = col_sizes;
  return res;
}
