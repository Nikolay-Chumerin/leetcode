typedef struct PriceIdx {
  float price;
  int idx;
} PriceIdx;

int comp(const void *a, const void *b) {
  const float pa = ((PriceIdx *)a)->price;
  const float pb = ((PriceIdx *)b)->price;
  if (pa < pb)
    return -1;
  if (pa > pb)
    return 1;
  return 0;
}

int paintWalls(int *cost, int cost_num, int *time, int time_num) {
  PriceIdx *prices = (PriceIdx *)malloc(cost_num * sizeof(PriceIdx));
  int i;
  for (i = 0; i < cost_num; ++i) {
    prices[i].idx = i;
    prices[i].cost = float(cost[i]) / time[i];
  }
  qsort(prices, cost_num, sizeof(PriceIdx), comp);

  free(prices);
  return 0;
}
