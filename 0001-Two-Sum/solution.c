/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int* result = (int*) malloc(2*sizeof(int));
    *returnSize = 2;
    for (int i = 1; i < numsSize; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] == target - nums[j]) {
                result[0] = j;
                result[1] = i;
                goto exit;
            }
        }  // j-loop
    }  // i-loop
exit:
    return result;
}
