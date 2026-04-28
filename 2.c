#include <stdio.h>
#include <stdlib.h>
#define table_size 105
#define q_size 10005

char a[table_size][table_size]; //массив символов
int dist[table_size][table_size]; //массив расстояний

int qx[q_size];
int qy[q_size];

int head, tail;

typedef struct coord{
    int x;
    int y;
}coord;

void BFS(coord start, int m, int n){
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    dist[start.x][start.y] = 0;
    qx[tail] = start.x;
    qy[tail] = start.y;
    tail++;

    while(head < tail){
        coord v;
        v.x = qx[head];
        v.y = qy[head];
        head++;

        for (int i = 0; i < 4; i++){
            int nx = v.x + dx[i];
            int ny = v.y + dy[i];

            if (nx < 0 || nx >= m || ny < 0 || ny >= n)
                continue;

            if (a[nx][ny] == 'X')
                continue;

            if (dist[nx][ny] == -1){
                dist[nx][ny] = dist[v.x][v.y] + 1;
                qx[tail] = nx;
                qy[tail] = ny;
                tail++;
            }
        }
    }
}

int main(){
    int m, n;
    coord start, finish;
    start.x = start.y = 0;
    finish.x = finish.y = 0;

    scanf("%d%d", &m, &n);

    for (int i = 0; i < m; i++){
        scanf("%s", a[i]);
    }

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            dist[i][j] = -1;

            if (a[i][j] == 'S'){
                start.x = i;
                start.y = j;
            }

            if (a[i][j] == 'F'){
                finish.x = i;
                finish.y = j;
            }
        }
    }

    head = 0;
    tail = 0;

    BFS(start, m, n);

    printf("%d", dist[finish.x][finish.y]);

    return 0;
}
