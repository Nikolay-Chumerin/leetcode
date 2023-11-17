#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITERATIONS (1024 * 16)
#define MIN_N (1)
#define MAX_N (16384)
#define MIN_VALUE (-32768)
#define MAX_VALUE (32767)

void quicksort(int *arr, const int beg, const int end) {
  if (beg >= end)
    return;
  const int pivot = arr[end];
  int i = beg;
  for (int j = beg; j < end; ++j) {
    const int aj = arr[j];
    if (aj >= pivot)
      continue;
    arr[j] = arr[i];
    arr[i++] = aj;
  }
  arr[end] = arr[i];
  arr[i] = pivot;
  quicksort(arr, beg, i - 1);
  quicksort(arr, i + 1, end);
} /* quicksort(...) */

void init_array(int *arr, const int n) {
  for (int i = 0; i < n; ++i) {
    arr[i] = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
  }
}

int is_sorted(const int *const arr, const int n) {
  for (int i = 1; i < n; ++i)
    if (arr[i - 1] > arr[i])
      return 0;
  return 1;
}

int random_test() {
  int arr[MAX_N];
  srand(time(NULL));
  for (int i = 0; i < MAX_ITERATIONS; ++i) {
    const int n = MIN_N + rand() % (MAX_N - MIN_N + 1);
    init_array(arr, n);
    quicksort(arr, 0, n - 1);
    if (!is_sorted(arr, n)) {
      printf("Found an array of length %d, which was not sorted!\n", n);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int large_array_test() {
#include "big_array.c"
  const int n = sizeof(arr) / sizeof(arr[0]);
  printf("Large array test: n=%d\n", n);
  quicksort(arr, 0, n - 1);
  if (!is_sorted(arr, n)) {
    printf("Large array of length %d, was not sorted correctly!\n", n);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int main() {
  int failed_tests_num = 0;
  // failed_tests_num += (EXIT_FAILURE == random_test());
  failed_tests_num += (EXIT_FAILURE == large_array_test());
  return failed_tests_num;
}
