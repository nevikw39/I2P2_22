/**                  _ _              _____ ___
 *  _ __   _____   _(_) | ____      _|___ // _ \
 * | '_ \ / _ \ \ / / | |/ /\ \ /\ / / |_ \ (_) |
 * | | | |  __/\ V /| |   <  \ V  V / ___) \__, |
 * |_| |_|\___| \_/ |_|_|\_\  \_/\_/ |____/  /_/
 **/
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef nevikw39
#else
#pragma message("hello, nevikw39")
#endif
#pragma message("GL; HF!")

#define N 100000

typedef struct _edge // the linked list node of edges of a vertex
{
    int v;
    struct _edge *next;
} edge;
edge *head[N], *tail[N];

void update(int *ptr, int x) // update the max value
{
    if (*ptr < x)
        *ptr = x;
}

int *dfs(int u, int p)
{
    int *arr = malloc(sizeof(int) << 1); // the state of the current root
    arr[0] = 0;
    arr[1] = 0;
    for (edge *ptr = head[u]; ptr; ptr = ptr->next)
    {
        if (ptr->v == p)
            continue;
        int *brr = dfs(ptr->v, u);
        update(arr, brr[0]);
        update(arr, arr[1] + 1 + brr[1]);
        update(arr + 1, 1 + brr[1]);
        free(brr);
    }
    return arr;
}

void free_list(edge *ptr)
{
    if (!ptr)
        return;
    free_list(ptr->next);
    free(ptr);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            tail[i] = head[i] = NULL;
        for (int i = 1; i < n; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            --u;
            --v;
            if (head[u] && tail[u])
                tail[u] = tail[u]->next = malloc(sizeof(edge));
            else
                head[u] = tail[u] = malloc(sizeof(edge));
            if (head[v] && tail[v])
                tail[v] = tail[v]->next = malloc(sizeof(edge));
            else
                head[v] = tail[v] = malloc(sizeof(edge));
            *tail[u] = (edge){.v = v, .next = NULL};
            *tail[v] = (edge){.v = u, .next = NULL};
        }
        printf("%d\n", dfs(0, -1)[0]);
        for (int i = 0; i < n; i++)
            free_list(head[i]);
    }
    return 0;
}