#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int v;
    struct Node* next;
}Node;

Node* createNode(int v, Node* next){
    Node* New = (Node*)malloc(sizeof(Node));
    New->v = v;
    New->next = next;
    return New;
}

void insert(int* heap, int* size, int value){
    (*size)++;
    heap[*size] = value;

    int i = *size;
    while(i > 1 && heap[i] < heap[i / 2]){
        int t = heap[i];
        heap[i] = heap[i / 2];
        heap[i / 2] = t;
        i /= 2;
    }
}

int getMin(int* heap, int* size){
    int res = heap[1];
    int x = heap[*size];
    (*size)--;

    int i = 1;
    while(i * 2 <= *size){
        int j = i * 2;
        if(j + 1 <= *size && heap[j + 1] < heap[j])
            j++;

        if(heap[j] >= x)
            break;

        heap[i] = heap[j];
        i = j;
    }

    heap[i] = x;
    return res;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    Node** a = (Node**)calloc(n + 1, sizeof(Node*));
    int* in = (int*)calloc(n + 1, sizeof(int));
    int* ans = (int*)malloc((n + 1) * sizeof(int));
    int* heap = (int*)malloc((n + 1) * sizeof(int));

    int size = 0;
    int cnt = 0;

    for(int i = 0; i < m; i++){
        int b, c;
        scanf("%d%d", &b, &c);
        a[b] = createNode(c, a[b]);
        in[c]++;
    }

    for(int i = 1; i <= n; i++){
        if(in[i] == 0)
            insert(heap, &size, i);
    }

    while(size > 0){
        int x = getMin(heap, &size);
        ans[cnt++] = x;

        Node* p = a[x];
        while(p != NULL){
            in[p->v]--;
            if(in[p->v] == 0)
                insert(heap, &size, p->v);
            p = p->next;
        }
    }

    if(cnt != n){
        printf("bad course");
        return 0;
    }

    for(int i = 0; i < cnt; i++){
        if(i > 0)
            printf(" ");
        printf("%d", ans[i]);
    }

    return 0;
}
