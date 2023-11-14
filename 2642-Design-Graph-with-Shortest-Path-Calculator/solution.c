/*
 * @lc app=leetcode id=2642 lang=c
 *
 * [2642] Design Graph With Shortest Path Calculator
 */

// @lc code=start
#define INF (2147483647)
#define MAX_NODES_NUM (100)
#define LIST_CAPACITY (MAX_NODES_NUM * (MAX_NODES_NUM - 1) / 2)

typedef struct {
  int n;                                 /* Number of graph nodes */
  int adj[MAX_NODES_NUM][MAX_NODES_NUM]; /* Graph adjacency matrix */
} Graph;

typedef struct {
  int node_idx;
  int weight;
} ListElement;

typedef struct {
  int size;                        /* List size */
  ListElement data[LIST_CAPACITY]; /* List data */
  int head_idx;
  int tail_idx;
} List;

List *list_create() {
  List *list = calloc(1, sizeof(List));
  list->size = 0;
  list->head_idx = 0;
  list->tail_idx = LIST_CAPACITY - 1;
  return list;
}

void list_push(List *list, const ListElement element) {
  if (list->size >= LIST_CAPACITY)
    return; /* error: can't push */
  ++list->size;
  list->tail_idx = (list->tail_idx + 1) % LIST_CAPACITY;
  list->data[list->tail_idx] = element;
}

ListElement list_pop(List *list) {
  ListElement ans = {.node_idx = -1, .weight = -1};
  if (list->size <= 0)
    return ans; /* error: can't pop */
  ans = list->data[list->head_idx];
  --list->size;
  list->head_idx = (list->head_idx + 1) % LIST_CAPACITY;
  return ans;
}

void list_add_or_update(List *list, const ListElement pair) {
  int i = list->head_idx;
  bool found = false;
  for (int procesed_num = 0; procesed_num < list->size; ++procesed_num) {
    found = (list->data[i].node_idx == pair.node_idx);
    if (found)
      break;
    i = (++i) % LIST_CAPACITY;
  }

  if (found) {
    list->data[i] = pair;
  } else {
    list_push(list, pair);
  }
} /* list_add_or_update(..) */

void list_free(List *list) {
  free(list);
  list = NULL;
}

Graph *graphCreate(int nodes_num, int **edges, int edges_num, int *edge_data_len) {
  Graph *graph = calloc(1, sizeof(Graph));
  graph->n = nodes_num;
  for (int i = 0; i < edges_num; ++i) {
    graph->adj[edges[i][0]][edges[i][1]] = edges[i][2];
  }
  return graph;
} /* graphCreate(...) */

void graphAddEdge(Graph *graph, int *edge_data, int edge_data_len) {
  graph->adj[edge_data[0]][edge_data[1]] = edge_data[2];
} /* graphAddEdge(...) */

int graphShortestPath(Graph *graph, int start_idx, int finish_idx) {
  int distance[MAX_NODES_NUM];
  for (int i = 0; i < graph->n; ++i)
    distance[i] = INF;
  distance[start_idx] = 0;
  List *s = list_create();
  list_push(s, (ListElement){.node_idx = start_idx, .weight = 0});
  while (s->size) {
    const ListElement pair = list_pop(s);
    const int from = pair.node_idx;
    for (int to = 0; to < graph->n; ++to) {
      if (!graph->adj[from][to])
        continue;
      const int new_distance = distance[from] + graph->adj[from][to];
      if (distance[to] > new_distance) {
        list_add_or_update(
            s, (ListElement){.node_idx = to, .weight = new_distance});
        distance[to] = new_distance;
      }
    } /* loop over graph nodes */
  }   /* main loop */
  list_free(s);
  const int ans = (distance[finish_idx] == INF) ? -1 : distance[finish_idx];
  return ans;
} /* graphShortestPath(...) */

void graphFree(Graph *graph) {
  free(graph);
  graph = NULL;
} /* graphFree(.) */

/**
 * Your Graph struct will be instantiated and called as such:
 * Graph* obj = graphCreate(n, edges, edgesSize, edgesColSize);
 * graphAddEdge(obj, edge, edgeSize);

 * int param_2 = graphShortestPath(obj, node1, node2);

 * graphFree(obj);
*/
// @lc code=end
