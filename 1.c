#include <stdio.h>
#include <stdlib.h>
#define INF 10000000
typedef struct Node{
    int v; //вершина
    int w; //weight
    struct Node* next;
}Node;

Node* a[105]; //массив списков
int dist[105]; //кратчайший путь
int used[105] = {0}; // ходили или нет

Node* createNode(int v, int w, Node* next){
    Node* New = (Node*)malloc(sizeof(Node));
    New->v = v;
    New->w = w;
    New->next = next;

    return New;
}

void deijkstra(int s1, int N){
    dist[s1] = 0;

    for(int i = 0; i < N; i++){

        int v = -1;
        for(int j = 1; j <= N; j++){
            if(used[j] == 0){
                if(v == -1)
                    v = j;
                else if(dist[j] < dist[v])
                    v = j;
            }
        }

        if(v == -1)
            break;

        if(dist[v] == INF)
            break;

        used[v] = 1;

        Node* p = a[v];
        while (p != NULL){
            int u = p->v;
            int w = p->w;

            if (dist[u] > dist[v] + w)
                dist[u] = dist[v] + w;

            p = p->next; 
        }
        
    }
    
}

int main(){
    int N, s1, s2;
    scanf("%d", &N);
    scanf("%d %d", &s1, &s2);

    for (int i = 1; i <= N; i++){
        dist[i] = INF;
        used[i] = 0;
    }

    int u, v, w;
    while (scanf("%d %d %d", &u, &v, &w) == 3){
        a[u] = createNode(v, w, a[u]);
        a[v] = createNode(u, w, a[v]);
    }

    deijkstra(s1, N);

    if (dist[s2] == INF)
        printf("no");
    else
        printf("%d", dist[s2]);

    return 0;
}
