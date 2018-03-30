/**
 * 多源最短路径-Floyd算法
 * 原理：动态规划
 * 
 * P-Code:
 * floyd(graph)
 *     dist = |V| * |V| array of minimum distances initialized to Pos-INF
 *     for (v: graph中的所有顶点)
 *         dist[v][v] = 0
 *     for ((v, u): graph中的所有边)
 *         dist[u][v] = graph[u][v]
 *     for (k: graph中的所有顶点)
 *         for (i: graph中的所有顶点)
 *             for (j: graph中的所有顶点)
 *                 if (dist[i][j] > dist[i][k] + dist[k][j])
 *                     dist[i][j] = dist[i][k] + dist[k][j]
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
    }
    return graph;
}

int *floyd(int *graph, size_t N)
{
    int *dist = (int *)malloc(sizeof(int) * N * N);
    for (int i = 0; i != N; ++i) {
        for (int j = 0; j != N; ++j)
            dist[i * N + j] = graph[i * N + j];
    }
    for (int k = 0; k != N; ++k) {
        for (int i = 0; i != N; ++i) {
            for (int j = 0; j != N; ++j) {
                if (dist[i * N + k] == -1 || dist[k * N + j] == -1)
                    continue;
                if (dist[i * N + j] == -1 || dist[i * N + j] > dist[i * N + k] + dist[k * N + j])
                    dist[i * N + j] = dist[i * N + k] + dist[k * N + j];
            }
        }
    }
    return dist;
}

//#define DEBUG
#ifdef DEBUG
int main()
{
    int *graph = generate_graph(4);
    int *dist = floyd(graph, 4);
    
    for (int i = 0; i != 4; ++i) {
        printf("[");
        for (int j = 0; j != 4; ++j)
            printf(" %d", dist[i * 4 + j]);
        printf(" ]\n");
    }
    
    return 0;
}
#endif
