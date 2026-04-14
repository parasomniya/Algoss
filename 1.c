#include <stdio.h>

#define MAXN 400
#define MAXM 79800

static int head[MAXN + 1];
static int to[MAXM + 1];
static int next_edge[MAXM + 1];
static int indegree[MAXN + 1];
static int heap[MAXN + 1];
static int order[MAXN + 1];

static void heap_push(int *size, int value) {
    int pos = ++(*size);
    heap[pos] = value;

    while (pos > 1 && heap[pos] < heap[pos / 2]) {
        int temp = heap[pos];
        heap[pos] = heap[pos / 2];
        heap[pos / 2] = temp;
        pos /= 2;
    }
}

static int heap_pop(int *size) {
    int result = heap[1];
    int value = heap[(*size)--];
    int pos = 1;

    while (pos * 2 <= *size) {
        int child = pos * 2;

        if (child + 1 <= *size && heap[child + 1] < heap[child]) {
            child++;
        }

        if (heap[child] >= value) {
            break;
        }

        heap[pos] = heap[child];
        pos = child;
    }

    heap[pos] = value;
    return result;
}

int main(void) {
    int n, m;
    int edge_count = 0;
    int heap_size = 0;
    int produced = 0;

    if (scanf("%d%d", &n, &m) != 2) {
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int b, a;
        scanf("%d%d", &b, &a);

        edge_count++;
        to[edge_count] = a;
        next_edge[edge_count] = head[b];
        head[b] = edge_count;
        indegree[a]++;
    }

    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            heap_push(&heap_size, i);
        }
    }

    while (heap_size > 0) {
        int v = heap_pop(&heap_size);
        order[produced++] = v;

        for (int edge = head[v]; edge != -1; edge = next_edge[edge]) {
            int u = to[edge];
            indegree[u]--;

            if (indegree[u] == 0) {
                heap_push(&heap_size, u);
            }
        }
    }

    if (produced != n) {
        printf("bad course");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", order[i]);
    }

    return 0;
}
