/**
 * 最小生成树-Kruskal算法
 * 原理：贪心算法
 * 
 * P-Code:
 * kruskal(graph)
 *     S = set of tree root-node initialized empty
 *     E = set of edge initialized empty
 *     for (v: graph中的所有顶点)
 *         add(v, S)
 *     for (e: graph中的所有边)
 *         add(e, E)
 *     for ((u, v): E中权值最小的边)
 *         if (u, v不在同一棵树中)
 *             u <- v合并两棵树
 *             remove(v, S)
 *         remove((u, v), E)
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
 * 3 -> 0
 * 0 -> 1
 * 4 -> 2
 * 5 -> 3
 * 1 -> 4
 * -1 -> 5
 * 4 -> 6
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using std::sort;

struct Edge {
    int v1;
    int v2;
    int weight;
};

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

int *kruskal(int *graph, size_t N_Vertex, size_t N_Edge, int *pweight)
{
    int *parent;
    Edge *e;
    int idx, p1, p2, cur;
    
    *pweight = 0;
    parent = (int *)malloc(sizeof(int) * N_Vertex);
    e = (Edge *)malloc(sizeof(Edge) * N_Edge);
    for (int i = 0; i != N_Vertex; ++i)
        parent[i] = -1;
    idx = 0;
    for (int i = 0; i != N_Vertex; ++i) {
        for (int j = i + 1; j != N_Vertex; ++j) {
            if (graph[i * N_Vertex + j] <= 0)
                continue;
            e[idx].v1 = i;
            e[idx].v2 = j;
            e[idx].weight = graph[i * N_Vertex + j];
            ++idx;
        }
    }
    if (idx != N_Edge)
        return NULL;
    sort(e, e + N_Edge, [](const Edge &l, const Edge &r) {
        return l.weight < r.weight;
    });
    for (int i = 0; i != N_Edge; ++i) {
        p1 = e[i].v1;
        p2 = e[i].v2;
        while (parent[p1] != -1)
            p1 = parent[p1];
        while (parent[p2] != -1)
            p2 = parent[p2];
        if (p1 == p2)
            continue;
        *pweight += e[i].weight;
        if (parent[e[i].v1] == -1 && parent[e[i].v2] == -1)
            parent[e[i].v1] = e[i].v2;
        else if (parent[e[i].v1] != -1 && parent[e[i].v2] != -1) {
            cur = e[i].v2;
            p1 = parent[cur];
            do {
                p2 = parent[p1];
                parent[p1] = cur;
                cur = p1;
                p1 = p2;
            } while (p1 != -1);
            parent[e[i].v2] = e[i].v1;
        } else {
            if (parent[e[i].v1] == -1)
                parent[e[i].v1] = e[i].v2;
            else
                parent[e[i].v2] = e[i].v1;
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
    int *parent = kruskal(graph, 7, 11, &weight);
    printf("weight: %d\n", weight);
    for (int i = 0; i != 7; ++i)
        printf("%d -> %d\n", parent[i], i);
    
    return 0;
}
#endif
