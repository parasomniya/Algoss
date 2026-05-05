#include <stdio.h>

#define sz 305
#define INF 4000000000000000000

unsigned long long a[sz][sz];
int nxt[sz][sz];

void init(){
    for(int i = 0; i < sz; i++){
        for(int j = 0; j < sz; j++){
            if(i == j){
                a[i][j] = 0;
                nxt[i][j] = i;
            }
            else{
                a[i][j] = INF;
                nxt[i][j] = -1;
            }
        }
    }
}

void add(int u, int v, int w){
    if((unsigned long long)w < a[u][v]){
        a[u][v] = (unsigned long long)w;
        a[v][u] = (unsigned long long)w;
        nxt[u][v] = v;
        nxt[v][u] = u;
    }
}

void f(int n){
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            if(a[i][k] == INF)
                continue;

            for(int j = 1; j <= n; j++){
                if(a[k][j] == INF)
                    continue;

                if(a[i][k] + a[k][j] < a[i][j]){
                    a[i][j] = a[i][k] + a[k][j];
                    nxt[i][j] = nxt[i][k];
                }
            }
        }
    }
}

int main(){
    int n, m, p, k;
    scanf("%d%d%d%d", &n, &m, &p, &k);

    init();

    for(int i = 0; i < m; i++){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }

    f(n);

    for(int i = 0; i < p; i++){
        int s, t;
        scanf("%d%d", &s, &t);

        if(nxt[s][t] == -1){
            printf("no\n");
            continue;
        }

        int way[sz];
        int cnt = 0;
        int cur = s;
        way[cnt++] = cur;

        while(cur != t){
            cur = nxt[cur][t];
            way[cnt++] = cur;
        }

        printf("%llu %d", a[s][t], cnt);
        for(int j = 0; j < cnt; j++)
            printf(" %d", way[j]);
        printf("\n");
    }

    for(int i = 0; i < k; i++){
        int s, t;
        scanf("%d%d", &s, &t);

        if(a[s][t] == INF)
            printf("no");
        else
            printf("%llu", a[s][t]);

        if(i + 1 < k)
            printf("\n");
    }

    return 0;
}
