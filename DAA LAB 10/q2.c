
#include <stdio.h>

#define MAX 10000

int parent[MAX];
int rank[MAX];
int land[MAX];

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

int unite(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY)
        return 0;

    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else
    {
        parent[rootY] = rootX;
        rank[rootX]++;
    }

    return 1;
}

int main()
{
    int R, C, K;
    int r, c, id, count = 0;
    int i, nr, nc, nid;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    printf("Enter rows, columns and operations: ");
    scanf("%d %d %d", &R, &C, &K);

    if (R <= 0 || C <= 0 || R * C > MAX ||
        K < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    for (i = 0; i < R * C; i++)
    {
        parent[i] = i;
        rank[i] = 0;
        land[i] = 0;
    }

    for (i = 0; i < K; i++)
    {
        printf("Enter land position (row column): ");
        scanf("%d %d", &r, &c);

        if (r < 0 || r >= R || c < 0 || c >= C)
        {
            printf("Invalid position. Islands = %d\n", count);
            continue;
        }

        id = r * C + c;

        if (land[id])
        {
            printf("Islands = %d\n", count);
            continue;
        }

        land[id] = 1;
        count++;

        for (int d = 0; d < 4; d++)
        {
            nr = r + dr[d];
            nc = c + dc[d];

            if (nr >= 0 && nr < R &&
                nc >= 0 && nc < C)
            {
                nid = nr * C + nc;

                if (land[nid] && unite(id, nid))
                    count--;
            }
        }

        printf("Islands = %d\n", count);
    }

    return 0;
}
