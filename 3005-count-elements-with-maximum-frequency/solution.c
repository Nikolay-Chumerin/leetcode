#define MAX_N (100)
int maxFrequencyElements(int* nums, int n) {
  int f[MAX_N + 1] = {0};
  int ans = 0;
  int max_f = 0;
  for (; n; --n) {
    const int curr_f = ++f[*nums++];
    if (curr_f < max_f) continue;
    if (curr_f == max_f) {
      ans += curr_f;
      continue;
    }
    // curr_f > max_f
    ans = curr_f;
    max_f = curr_f;
  }  // loop
  return ans;   
}