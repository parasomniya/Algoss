#include <stdio.h>
#include <stdlib.h>
#define table_size 200005

//список смежности
typedef struct Node{
    int v;
    struct Node* next;
}Node;

Node* a[200005]; //массив списков смежностей
//a[i] — список всех вершин, в которые можно попасть из i
int dist[200005]; // расстояние от 1, если -1 то недостижима
int q[200005]; // очередь
int tail, head;

//функция создания узла
Node* createNode(int v, Node* next){
    Node* New = (Node*)malloc(sizeof(Node));
    New->v = v;
    New->next = next;
    return New;
}

//BFS
void BFS(int start){
    dist[start] = 0;
    q[tail++] = start; // это в main потом перенести

    while(head < tail){
        int v = q[head++];

        Node* p = a[v];
        while (p != NULL){
            int u = p->v;

            if(dist[u] == -1){
                dist[u] = dist[v] + 1;
                q[tail++] = u;
            }

            p = p->next;
        }
    }
}

int main(){
    int N, M;
    int start = 1;

    head = 0;
    tail = 0;

    scanf("%d %d", &N, &M);
    
    for(int i = 1; i <= N; i++)
        dist[i] = -1;
    

    for (int i = 0; i < M; i++){
        int u, v;
        scanf("%d %d", &u, &v);

        a[u] = createNode(v, a[u]);
        //u->v
        //добавление вершины v в a[u]
    }

    BFS(start);

    for (int i = 1; i <= N; i++)
        printf("%d\n", dist[i]);
    
    return 0;
}
