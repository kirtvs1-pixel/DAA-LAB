
#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int color[MAX];
int queue[MAX];
int V;

int isBipartite()
{
    int i, u, v;
    int front, rear;

    for (i = 0; i < V; i++)
        color[i] = -1;

    for (i = 0; i < V; i++)
    {
        if (color[i] == -1)
        {
            front = 0;
            rear = 0;

            queue[rear++] = i;
            color[i] = 0;

            while (front < rear)
            {
                u = queue[front++];

                for (v = 0; v < V; v++)
                {
                    if (graph[u][v] == 1)
                    {
                        if (color[v] == -1)
                        {
                            color[v] = 1 - color[u];
                            queue[rear++] = v;
                        }
                        else if (color[v] == color[u])
                        {
                            return 0;
                        }
                    }
                }
            }
        }
    }

    return 1;
}

int main()
{
    int E, i, u, v;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    if (V < 1 || V > MAX || E < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter edges (vertices numbered 0 to %d):\n", V - 1);

    for (i = 0; i < E; i++)
    {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            printf("Invalid edge. Skipped.\n");
            continue;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;

        if (isBipartite())
        {
            printf("Edge (%d, %d) accepted.\n", u, v);
        }
        else
        {
            graph[u][v] = 0;
            graph[v][u] = 0;

            printf("Edge (%d, %d) rejected: "
                   "Graph is not bipartite.\n", u, v);
        }
    }

    printf("\nFinal graph is bipartite.\n");

    return 0;
}
