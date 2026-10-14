
#include <stdio.h>

#define MAX 1000

int parent[MAX];
int active[MAX];
int weight[MAX];
int componentSum[MAX];
int graph[MAX][MAX];
int order[MAX];
int answer[MAX];
int V;

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void unite(int u, int v)
{
    int rootU = find(u);
    int rootV = find(v);

    if (rootU == rootV)
        return;

    parent[rootV] = rootU;
    componentSum[rootU] += componentSum[rootV];
}

int getMaximum()
{
    int i, root;
    int maximum = 0;

    for (i = 0; i < V; i++)
    {
        if (active[i])
        {
            root = find(i);

            if (componentSum[root] > maximum)
                maximum = componentSum[root];
        }
    }

    return maximum;
}

int main()
{
    int E, i, u, v, x;

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    if (V <= 0 || V > MAX || E < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter vertex weights:\n");

    for (i = 0; i < V; i++)
    {
        scanf("%d", &weight[i]);
        parent[i] = i;
        active[i] = 0;
        componentSum[i] = 0;
    }

    printf("Enter edges (vertices 0 to %d):\n", V - 1);

    for (i = 0; i < E; i++)
    {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            printf("Invalid edge.\n");
            return 1;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    printf("Enter deletion order:\n");

    for (i = 0; i < V; i++)
    {
        scanf("%d", &order[i]);

        if (order[i] < 0 || order[i] >= V)
        {
            printf("Invalid vertex.\n");
            return 1;
        }
    }

    /* Add vertices in reverse deletion order */
    for (i = V - 1; i >= 0; i--)
    {
        x = order[i];

        active[x] = 1;
        parent[x] = x;
        componentSum[x] = weight[x];

        for (int j = 0; j < V; j++)
        {
            if (graph[x][j] && active[j])
                unite(x, j);
        }

        answer[i] = getMaximum();
    }

    printf("\nMaximum component weight after each deletion:\n");

    for (i = 0; i < V; i++)
        printf("%d ", answer[i]);

    printf("\n");

    return 0;
}

