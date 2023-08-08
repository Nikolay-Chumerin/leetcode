/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** generateParenthesis(int n, int* returnSize) {
    char ** ans = (char**)malloc(12870*sizeof(char*));
    *returnSize = 0;
    const int max_i = 1 << (2*n);
    for (int i = 0; i < max_i; ++i) {
        if (__builtin_popcount(i) != n) continue;  // continue if number of set-bits (in i) != n
        int j = 0;
        int ii = i;
        for (int k = 0; j>=0 && k < 2*n; ++k, ii >>= 1) {
            // Lowest bit of ii: 1 <=> ')', 0 <=> '(' 
            j += 2 * (ii & 1) - 1; 
        }
        if (j == 0 ) {
            // found correct combination
            char * combination = malloc(2 * n + 1);
            ii = i;
            for (int k = 0; k < 2*n; ++k, ii >>=1) {
                combination[k] = (ii & 1) ? '(' : ')';                
            }
            combination[2*n] = 0;
            ans[(*returnSize)++] = combination;
        }  // found branch
    }  // i-loop
    return ans;
}