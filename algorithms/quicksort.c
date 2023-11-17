void quicksort(int *arr, const int beg, const int end) {
  if (beg >= end) return;
  const int pivot = arr[end];
  int i = beg;
  for (int j = beg; j < end; ++j) {
    const int aj = arr[j];
    if (aj >= pivot) continue;
    arr[j] = arr[i];
    arr[i++] = aj;
  }
  arr[end] = arr[i];
  arr[i] = pivot;
  quicksort(arr, beg, i - 1);
  quicksort(arr, i + 1, end);
}  /* quicksort(...) */
