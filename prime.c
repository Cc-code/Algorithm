/**
 * 最小生成树-Prime算法
 * 原理：贪心算法
 * 
 * P-Code:
 * prime(graph, start_v)
 *     dist = |V| array of distance from tree initialized Pos-INF
 *     for (v: start_v的所有邻接点)
 *         dist[v] = graph[start_v][v]
 *         parent[v] = start_v
 *     dist[start_v] = 0
 *     while (true)
 *         v = 下一个离生成树最近的节点
 *         if (v不存在)
 *             break
 *         dist[v] = 0
 *         for (u: v的所有未被访问的邻接点)
 *             if (graph[v][u] < dist[u])
 *                 dist[u] = graph[v][u]
 *                 parent[u] = v
 * 
 * Example Input:
 * 0 1 7
 * 0 3 5
 * 1 2 8
 * 1 3 9
 * 1 4 7
 * 2 4 5
 * 3 4 15
 * 3 5 6
 * 4 5 8
 * 4 6 9
 * 5 6 11
 * 
 * Example Output:
 * weight: 39
 * 0 -> 0
 * 0 -> 1
 * 4 -> 2
 * 0 -> 3
 * 1 -> 4
 * 3 -> 5
 * 4 -> 6
 */

#include <stdio.h>
#include <stdlib.h>

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

int *prime(int *graph, size_t N, int start_v, int *pweight)
{
    int *dist, *parent, min, v;
    *pweight = 0;
    
    if (start_v < 0 || start_v >= N)
        return NULL;
    dist = (int *)malloc(sizeof(int) * N);
    parent = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i != N; ++i) {
        dist[i] = graph[start_v * N + i];
        if (graph[start_v * N + i] != -1)
            parent[i] = start_v;
    }
    for (int i = 1; i != N; ++i) {
        min = -1;
        for (int j = 0; j != N; ++j) {
            if (dist[j] <= 0)
                continue;
            if (min == -1 || dist[j] < min) {
                min = dist[j];
                v = j;
            }
        }
        dist[v] = 0;
        *pweight += min;
        for (int j = 0; j != N; ++j) {
            if (graph[v * N + j] <= 0)
                continue;
            if (dist[j] == -1 || graph[v * N + j] < dist[j]) {
                dist[j] = graph[v * N + j];
                parent[j] = v;
            }
        }
    }
    return parent;
}

//#define DEBUG
#ifdef DEBUG
int main()
{
    int *graph = generate_graph(7);
    int weight;
    int *parent = prime(graph, 7, 0, &weight);
    printf("weight: %d\n", weight);
    for (int i = 0; i != 7; ++i)
        printf("%d -> %d\n", parent[i], i);
    
    return 0;
}
#endif
