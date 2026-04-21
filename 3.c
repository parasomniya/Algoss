#include <stdio.h>

#define MAXN 20005
#define MAXM 400005

int head[MAXN];
int to[MAXM];
int next[MAXM];
int comp[MAXN];
int cnt = 0;

void addEdge(int a, int b){
    cnt++;
    to[cnt] = b;
    next[cnt] = head[a];
    head[a] = cnt;
}

void dfs(int v, int color){
    comp[v] = color;

    for (int i = head[v]; i != 0; i = next[i]){
        int u = to[i];

        if (comp[u] == 0)
            dfs(u, color);
    }
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++){
        int a, b;
        scanf("%d%d", &a, &b);

        addEdge(a, b);
        addEdge(b, a);
    }

    int color = 0;

    for (int i = 1; i <= n; i++){
        if (comp[i] == 0){
            color++;
            dfs(i, color);
        }
    }

    printf("%d\n", color);

    for (int i = 1; i <= n; i++){
        printf("%d ", comp[i]);
    }

    return 0;
}
