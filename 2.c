#include <stdio.h>

int a[105][105];
int used[105];

void dfs(int v, int n){
    used[v] = 1;

    for (int i = 1; i <= n; i++){
        if (a[v][i] == 1 && used[i] == 0)
            dfs(i, n);
    }
}

int main(){
    int n;
    scanf("%d", &n);

    int x, y;
    while (scanf("%d%d", &x, &y) == 2){
        a[x][y] = 1;
        a[y][x] = 1;
    }

    int cnt = 0;

    for (int i = 1; i <= n; i++){
        if (used[i] == 0){
            cnt++;
            dfs(i, n);
        }
    }

    printf("%d", cnt + 1);

    return 0;
}
