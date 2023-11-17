void quicksort(int *arr, const int low, const int high) {
  if (low >= high)
    return;
  int middle = low + (high - low) / 2;
  int pivot = arr[middle];

  int i = low, j = high;
  while (i <= j) {
    while (arr[i] < pivot) {
      i++;
    }
    while (arr[j] > pivot) {
      j--;
    }

    if (i <= j) {
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
      i++;
      j--;
    }
  }

  if (low < j) {
    quicksort(arr, low, j);
  }
  if (high > i) {
    quicksort(arr, i, high);
  }
}
/**************************************************************/
int partition(int *nums, int left, int right) {
  int pivot = nums[left];
  int first = left;
  while (left < right) {
    while (left < right & nums[right] >= pivot) {
      right--;
    }
    while (left < right & nums[left] <= pivot) {
      left++;
    }
    if (left < right) {
      int tem = nums[right];
      nums[right] = nums[left];
      nums[left] = tem;
    };
  }
  nums[first] = nums[left];
  nums[left] = pivot;
  return left;
}

void quicksort_with_partition(int arr[], const int left, const int right) {
  if (left > right)
    return;
  int j = partition(arr, left, right);
  quicksort(arr, left, j - 1);
  quicksort(arr, j + 1, right);
}
/**************************************************************/
void my_quicksort(int *arr, const int beg, const int end) {
  if (beg >= end)
    return;
#ifdef USE_END_FOR_PIVOT
#define PIVOT_IDX end
#else
#define PIVOT_IDX ((beg + end) / 2)
#endif
  const int pivot = arr[PIVOT_IDX];
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
  my_quicksort(arr, beg, i - 1);
  my_quicksort(arr, i + 1, end);
} /* my_quicksort(...) */
