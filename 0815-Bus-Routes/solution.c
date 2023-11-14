/*
 * @lc app=leetcode id=0815 lang=c
 *
 * [0815] Bus Routes
 */

// @lc code=start

#include <limits.h>
#include <stdbool.h>

#define STOPS_MAX_NUM (100000)
#define STOP_MAX_IDX (1000000)
#define STOP_MIN_IDX (1)
#define STOP_EMPTY_IDX (0)
#define ROUTES_MAX_NUM (500)
#define INF (INT_MAX)
#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x < y ? y : x)

/* Bus stop info */
typedef struct {
  int tag;
  int routes_num;
  int *routes;
} Stop;

int tag2idx[STOP_MAX_IDX]; /* prefilled with zeros == STOP_EMPTY_IDX */
#define TAG2IDX(tag) (tag2idx[tag] - STOP_MIN_IDX)
bool route_connection[ROUTES_MAX_NUM * ROUTES_MAX_NUM];
#define ROUTES_PAIR_TO_IDX(i, j) (i * routes_num + j)
#define ROUTES_CONNECTED(i, j) (route_connection[ROUTES_PAIR_TO_IDX(i, j)])
#define CONNECT_ROUTES(i, j) (route_connection[ROUTES_PAIR_TO_IDX(i, j)] = true)

/******************************************************************************/
void print_stops(const Stop *stops, const int stops_num) {
  printf("Stops num=%d, list:\n", stops_num);
  for (int i = 0; i < stops_num; ++i) {
    const int stop_tag = stops[i].tag;
    printf("%d (%d):", i, stop_tag);
    for (int j = 0; j < stops[i].routes_num; ++j)
      printf(" %d", stops[i].routes[j]);
    printf("\n");
  } /* loop over stops*/
} /* print_stops(..) */

/******************************************************************************/
void print_routes(const int routes_num) {
  printf("Routes num=%d, matrix:\n", routes_num);
  for (int i = 0; i < routes_num; ++i) {
    for (int j = 0; j < routes_num; ++j)
      printf(" %d", ROUTES_CONNECTED(i, j));
    printf("\n");
  } /* loop over routes*/
} /* print_routes(.) */

/******************************************************************************/
int wave(const int start, const int finish, const int routes_num) {
  printf("searching path from node (bus route) #%d to #%d\n", start, finish);
  int *r = malloc(routes_num * sizeof(int));
  for (int i = 0; i < routes_num; ++i)
    r[i] = INF;
  r[start] = 0;
  for (int step = 0; step < routes_num; ++step) {
    const int next_step = step + 1;
    for (int from = 0; from < routes_num; ++from) {
      if (r[from] != step)
        continue;
      for (int to = 0; to < routes_num; ++to) {
        if (from == to || !ROUTES_CONNECTED(from, to))
          continue;
        if (r[to] > next_step)
          r[to] = next_step;
      } /* to-loop */
    }   /* from-loop */
    if (r[finish] != INF)
      return r[finish];
  } /* step-loop */
  return -1;
} /* int wave(...) */

/******************************************************************************/
int numBusesToDestination(int **routes, int routes_num, int *route_lengths,
                          int source_bus_stop, int destination_bus_stop) {
  Stop *stops = calloc(STOPS_MAX_NUM, sizeof(Stop));
  memset(tag2idx, 0, sizeof(tag2idx));
  memset(route_connection, 0, sizeof(route_connection));
  int stops_num = 0;
  int min_buses;
  bool src_and_dst_on_one_route = false;
  /* Fill out stops[] and tag2idx[] arrays */
  for (int route_idx = 0; route_idx < routes_num; ++route_idx) {
    const int *route = routes[route_idx];
    const int route_len = route_lengths[route_idx];
    bool src_in = false;
    bool dst_in = false;
    for (int i = 0; i < route_len; ++i) {
      const int stop_tag = route[i];
      src_in |= (stop_tag == source_bus_stop);
      dst_in |= (stop_tag == destination_bus_stop);
      int stop_idx = TAG2IDX(stop_tag);
      // printf("stop_tag=%d stops_num=%d stop_idx=%d\n", stop_tag, stops_num,
      // stop_idx);
      if (stop_idx < 0) {
        /* found a new stop, let's add it to the list */
        stop_idx = stops_num++;
        tag2idx[stop_tag] =
            stop_idx + STOP_MIN_IDX; /* kinda hash-table for tag->idx*/
        stops[stop_idx].tag = stop_tag;
        stops[stop_idx].routes = malloc(ROUTES_MAX_NUM * sizeof(int));
        stops[stop_idx].routes_num = 0;
      }
      const int stop_route_idx = stops[stop_idx].routes_num;
      stops[stop_idx].routes[stop_route_idx] = route_idx;
      ++stops[stop_idx].routes_num;
    } /* loop over stops on the current route */
    src_and_dst_on_one_route |= (src_in && dst_in);
  } /* loop over routes */

  if (src_and_dst_on_one_route) {
    min_buses = 1;
    goto free_and_exit;
  }
  print_stops(stops, stops_num);

  /* Create route connection graph */
  for (int i = 0; i < routes_num; ++i)
    CONNECT_ROUTES(i, i);
  for (int stop_idx = 0; stop_idx < stops_num; ++stop_idx) {
    const int stop_routes_num = stops[stop_idx].routes_num;
    // printf("stop_idx=%d stop_routes_num=%d\n", stop_idx, stop_routes_num);
    if (stop_routes_num < 2)
      continue;
    for (int i = 0; i < stop_routes_num - 1; ++i) {
      const int route_i = stops[stop_idx].routes[i];
      for (int j = i + 1; j < stop_routes_num; ++j) {
        const int route_j = stops[stop_idx].routes[j];
        CONNECT_ROUTES(route_i, route_j);
        CONNECT_ROUTES(route_j, route_i);
      } /* j-loop */
    }   /* i-loop */
  }     /* loop over stops*/
  print_routes(routes_num);

  min_buses = routes_num + 1;
  const int src_stop_idx = TAG2IDX(source_bus_stop);
  const int dst_stop_idx = TAG2IDX(destination_bus_stop);

  for (int src_idx = 0; src_idx < stops[src_stop_idx].routes_num; ++src_idx) {
    const int src_route_idx = stops[src_stop_idx].routes[src_idx];
    printf("src_idx=%d src_route_idx=%d\n", src_idx, src_route_idx);
    for (int dst_idx = 0; dst_idx < stops[dst_stop_idx].routes_num; ++dst_idx) {
      const int dst_route_idx = stops[dst_stop_idx].routes[dst_idx];
      printf("  dst_idx=%d dst_route_idx=%d\n", dst_idx, dst_route_idx);
      int buses_num = dfs(src_route_idx, dst_route_idx, routes_num);
      printf("    buses_num=%d\n", buses_num);
      if (buses_num > 0 && buses_num < min_buses)
        min_buses = buses_num;
    } /* loop over routes passing through the destination_bus_stop */
  }   /* loop over routes passing through the destination_bus_stop */

free_and_exit:
  /* free memory */
  for (int i = 0; i < stops_num; ++i) {
    free(stops[i].routes);
    stops[i].routes = NULL;
    stops[i].routes_num = 0;
  }
  free(stops);
  return min_buses <= routes_num ? min_buses : -1;
}
// @lc code=end
