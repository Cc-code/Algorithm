/**
 * 广度优先遍历-BFS
 * 
 * P-Code:
 * bfs(graph, start_v)
 *     print start_v
 *     visited[start_v] = true
 *     enqueue(start_v, q)
 *     while (!empty(q))
 *         v = front(s)
 *         dequeue(v, q)
 *         for (v2: v 的所有未被访问的邻接点) 
 *             print v2
 *             visited[v2] = true
 *             enqueue(v2, 1)
 * 
 * Example Input:
 * 0 1
 * 0 2
 * 0 3
 * 1 4
 * 2 5
 * 3 6
 * 1 5
 * 3 5
 * 
 * Example Output:
 * [ 0 1 2 3 4 5 6 ]
 */

#include <stdio.h>
#include <stdlib.h>
#include <queue>
using std::queue;

static int *generate_graph(size_t n)
{
    int v1, v2;
    int *graph = (int *)malloc(sizeof(int) * n * n);
    
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != n; ++j) {
            if (i == j)
                graph[i * n + j] = 0;
            else
                graph[i * n + j] = -1;
        }
    }
    while (scanf("%d%d", &v1, &v2) == 2) {
        if (v1 < 0 || v1 >= n) {
            printf("input error: vertex %d not fount!\n", v1);
            continue;
        }
        if (v2 < 0 || v2 >= n) {
            printf("input error: vertex %d not fount!\n", v2);
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
        graph[v1 * n + v2] = 1;
        graph[v2 * n + v1] = 1;
    }
    return graph;
}

void bfs(int *graph, size_t N, int start_v)
{
    queue<int> q;
    bool *visited;
    int v;
    
    if (start_v < 0 || start_v >= N)
        return;
     visited = (bool *)malloc(sizeof(bool) * N);
     for (int i = 0; i != N; ++i)
         visited[i] = false;
     
     printf("[ %d", start_v);
     visited[start_v] = true;
     q.push(start_v);
     while (!q.empty()) {
         v = q.front();
         q.pop();
         for (int i = 0; i != N; ++i) {
             if (graph[v * N + i] > 0 && !visited[i]) {
                 printf(" %d", i);
                 visited[i] = true;
                 q.push(i);
             }
         }
     }
     printf(" ]\n");
}

//#define DEBUG
#ifdef DEBUG
int main()
{
    int *graph = generate_graph(7);
    bfs(graph, 7, 0);
    
    return 0;
}
#endif
