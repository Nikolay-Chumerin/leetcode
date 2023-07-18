double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2,
                              int nums2Size) {
  int i1, i2;
  int prev, curr;
  const int med_i = 1 + (nums1Size + nums2Size) / 2;
  for (i1 = i2 = 0; i1 + i2 < med_i;) {
    prev = curr;
    if (i1 < nums1Size) {
      curr = nums1[i1++];
      if ((i2 < nums2Size) && (curr > nums2[i2])) {
        curr = nums2[i2++];
        --i1;
      }
    } else {
      curr = nums2[i2++];
    }
  } // loop
  return ((nums1Size + nums2Size) % 2) ? (double)curr
                                       : (double)(curr + prev) / 2.0;
}