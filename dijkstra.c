/**
 * 单源最短路径-Dijkstra算法
 * 原理：贪心算法
 * 
 * P-Code:
 * dijkstra(graph, start_v)
 *     for (v: graph中的所有顶点)
 *         visited[v] = false
 *         dist[v] = infinity
 *         previous[v] = undefined
 *     dist[start_v] = 0
 *     while (存在没有被访问的顶点)
 *         u = extract_min_from_unvisited(graph)
 *         visited[u] = true
 *         for (v: u的所有邻接点)
 *             if (dist[v] > dist[u] + graph[u, v])
 *                 dist[v] = dist[u] + graph[u, v]
 *                 previous[v] = u
 * 
 * Example Input:
 * 0 1 1
 * 0 5 3
 * 0 6 3
 * 1 2 2
 * 2 3 2
 * 2 5 1
 * 3 4 1
 * 4 5 2
 * 4 6 4
 * 5 6 1
 * 
 * Example Ouptut:
 * [ 0 1 3 5 5 3 3 ]
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int *generate_graph(size_t n)
{
    int v1, v2, w;
    int *graph = (int *)malloc(sizeof(int) * n * n);
    
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            if (i == j)
                graph[i * n + j] = 0;
            else
                graph[i * n + j] = -1;
        }
    }
    while (scanf("%d%d%d", &v1, &v2, &w) == 3) {
        if (v1 < 0 || v1 >= n) {
            printf("input error: vertex %d not fount!\n", v1);
            continue;
        }
        if (v2 < 0 || v2 >= n) {
            printf("input error: vertex %d not fount!\n", v2);
            continue;
        }
        if (w < 0) {
            printf("input error: weight must greater than 0\n");
            continue;
        }
        if (v1 == v2) {
            printf("input error: <%d, %d> must be 0\n", v1, v2);
            continue;
        }
        if (graph[v1 * n + v2] != -1) {
            printf("input error: <%d, %d> initialized\n", v1, v2);
            continue;
        }
        graph[v1 * n + v2] = w;
        graph[v2 * n + v1] = w;
    }
    return graph;
}

int *dijkstra(int *graph, size_t N, int start_v)
{
    bool *visited;
    int unvisited, u, min;
    int *dist;
    int *previous;
    
    if (start_v < 0 || start_v >= N)
        return 0;
    visited = (bool *)malloc(sizeof(bool) * N);
    dist = (int *)malloc(sizeof(int) * N);
    previous = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i != N; ++i) {
        visited[i] = false;
        dist[i] = -1;
        previous[i] = -1;
    }
    unvisited = N;
    dist[start_v] = 0;
    while (unvisited) {
        min = -1;
        for (int i = 0; i != N; ++i) {
            if (visited[i] || dist[i] == -1)
                continue;
            if (min == -1 || dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }
        visited[u] = true;
        --unvisited;
        for (int i = 0; i != N; ++i) {
            if (graph[u * N + i] <= 0)
                continue;
            if (dist[i] == -1 || dist[i] > dist[u] + graph[u * N + i]) {
                dist[i] = dist[u] + graph[u * N + i];
                previous[i] = u;
            }
        }
    }
    return dist;
}

//#define DEBUG
#ifdef DEBUG
int main()
{
    int *graph = generate_graph(7);
    int *dist = dijkstra(graph, 7, 0);
    
    printf("[");
    for (int i = 0; i != 7; ++i)
        printf(" %d", dist[i]);
    printf(" ]\n");
    
    return 0;
}
#endif
