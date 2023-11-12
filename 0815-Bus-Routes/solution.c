/*
 * @lc app=leetcode id=815 lang=c
 *
 * [815] Bus Routes
 */

// @lc code=start

#define STOPS_MAX_NUM (100000)
#define STOP_MAX_IDX (1000000)
#define STOP_MIN_IDX (1)
#define STOP_EMPTY_IDX (0)
#define ROUTES_MAX_NUM (500)

/* Bus stop info */
typedef struct {
  int tag;
  int routes_num;
  int *routes;
} Stop;

int tag2idx[STOP_MAX_IDX]; /* prefilled with zeros == STOP_EMPTY_IDX */
#define TAG2IDX(tag) (tag2idx[tag] - STOP_MIN_IDX)

int numBusesToDestination(int **routes, int routes_num, int *route_lengths,
                          int source, int target) {
  Stop *stops = malloc(STOPS_MAX_NUM * sizeof(Stop));
  int stops_num = 0;

  /* Fill out stops[] and tag2idx[] arrays */
  for (int route_idx = 0; route_idx < routes_num; ++route_idx) {
    const int *route = routes[route_idx];
    const int route_len = route_lengths[route_idx];
    for (int i = 0; i < route_len; ++i) {
      const int stop_tag = route[i];
      int stop_idx = TAG2IDX(stop_tag);
      if (stop_idx < 0) {
        /* found a new stop, let's add it to the list */
        stop_idx = stops_num++;
        tag2idx[stop_tag] = stop_idx + STOP_MIN_IDX;  /* kinda hash-table for tag->idx*/
        stops[stop_idx].tag = stop_tag;
        stops[stop_idx].routes = (int*) malloc(ROUTES_MAX_NUM * sizeof(int));
        stops[stop_idx].routes_num = 0;
      }
      const int stop_route_idx = stops[stop_idx].routes_num;
      stops[stop_idx].routes[stop_route_idx] = route_idx;
      ++stops[stop_idx].routes_num;
    } /* loop over stops on the current route */
  }   /* loop over routes */


  for (int i = 0; i < stops_num; ++i) {
    const int stop_tag = stops[i].tag;
    printf("%d (%d):", i, stop_tag);
    for (int j = 0; j < stops[i].routes_num; ++j)
      printf(" %d", stops[i].routes[j]);
    printf("\n");
  }  /* loop over stops*/

  /* free memory */
  for (int i = 0; i < stops_num; ++i) {
    free(stops[i].routes);
    stops[i].routes = NULL;
    stops[i].routes_num = 0;
  }
  free(stops);
  return -1;
}
// @lc code=end
