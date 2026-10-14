
#include <stdio.h>

#define MAX 1000

int parent[MAX];
int size[MAX];
int weight[MAX];

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

    if (size[rootU] < size[rootV])
    {
        int temp = rootU;
        rootU = rootV;
        rootV = temp;
    }

    parent[rootV] = rootU;
    size[rootU] += size[rootV];
    weight[rootU] += weight[rootV];
}

int maxWeightComponent(int V, int K)
{
    int i, root;
    int maximum = 0;
    int found = 0;

    for (i = 0; i < V; i++)
    {
        root = find(i);

        if (root == i && size[root] <= K)
        {
            if (!found || weight[root] > maximum)
            {
                maximum = weight[root];
                found = 1;
            }
        }
    }

    if (!found)
        return -1;

    return maximum;
}

int main()
{
    int V, E, K;
    int i, u, v, answer;

    printf("Enter vertices, edges and K: ");
    scanf("%d %d %d", &V, &E, &K);

    if (V <= 0 || V > MAX || E < 0 ||
        K < 1 || K > V)
    {
        printf("Invalid input.\n");
        return 1;
    }

    for (i = 0; i < V; i++)
    {
        printf("Enter weight of vertex %d: ", i);
        scanf("%d", &weight[i]);

        parent[i] = i;
        size[i] = 1;
    }

    printf("Enter edges (vertices 0 to %d):\n", V - 1);

    for (i = 0; i < E; i++)
    {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            printf("Invalid edge. Skipped.\n");
            continue;
        }

        unite(u, v);

        answer = maxWeightComponent(V, K);

        printf("After edge (%d, %d): ", u, v);

        if (answer == -1)
            printf("No eligible component\n");
        else
            printf("Maximum component weight = %d\n", answer);
    }

    return 0;
}
