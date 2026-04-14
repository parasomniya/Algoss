#include <stdio.h>
#include <stdlib.h>

#define buf 65536

typedef struct Node{
    int num;
    int s;
}Node;

char in[buf];
int inPos = 0;
int inLen = 0;

char out[buf];
int outPos = 0;

int getCharFast(){
    if (inPos >= inLen){
        inLen = fread(in, 1, buf, stdin);
        inPos = 0;

        if (inLen == 0)
            return EOF;
    }

    return in[inPos++];
}

int getInt(){
    int c = getCharFast();
    int x = 0;

    while (c <= ' ' && c != EOF)
        c = getCharFast();

    while (c > ' ' && c != EOF){
        x = x * 10 + c - '0';
        c = getCharFast();
    }

    return x;
}

void flush(){
    if (outPos > 0){
        fwrite(out, 1, outPos, stdout);
        outPos = 0;
    }
}

void putCharFast(char c){
    if (outPos == buf)
        flush();

    out[outPos++] = c;
}

void putInt(int x){
    char s[20];
    int cnt = 0;

    if (x == 0){
        putCharFast('0');
        return;
    }

    if (x < 0){
        putCharFast('-');
        x = -x;
    }

    while (x > 0){
        s[cnt++] = x % 10 + '0';
        x /= 10;
    }

    while (cnt > 0)
        putCharFast(s[--cnt]);
}

int main(){
    int n = getInt();

    Node* a = (Node*)malloc((n + 1) * sizeof(Node));
    int* ans = (int*)calloc(n + 1, sizeof(int));
    int* st = (int*)malloc((n + 1) * sizeof(int));

    for (int i = 1; i <= n; i++){
        int p = getInt();
        int s = getInt();

        a[p].num = i;
        a[p].s = s;
    }

    int top = 0;

    for (int i = 1; i <= n; i++){
        int last = 0;

        while (top > 0 && a[st[top]].s > a[i].s){
            last = st[top];
            top--;
        }

        if (top > 0)
            ans[a[i].num] = -a[st[top]].num;

        if (last != 0)
            ans[a[last].num] = a[i].num;

        top++;
        st[top] = i;
    }

    for (int i = 1; i <= n; i++){
        if (i > 1)
            putCharFast(' ');

        putInt(ans[i]);
    }

    flush();
    return 0;
}
