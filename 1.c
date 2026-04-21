#include <stdio.h>

int a[55][55];
int used[55];

void dfs(int v, int n){
    used[v] = 1;

    for (int i = 1; i <= n; i++){
        if (a[v][i] == 1 && used[i] == 0)
            dfs(i, n);
    }
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++){
        int x, y;
        scanf("%d%d", &x, &y);

        a[x][y] = 1;
        a[y][x] = 1;
    }

    int s;
    scanf("%d", &s);

    int shamans[15];

    for (int i = 0; i < s; i++)
        scanf("%d", &shamans[i]);

    dfs(shamans[0], n);

    for (int i = 0; i < s; i++){
        if (used[shamans[i]] == 0){
            printf("NO");
            return 0;
        }
    }

    printf("YES");

    return 0;
}
