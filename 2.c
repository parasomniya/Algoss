#include <stdio.h>
#include <stdlib.h>

#define buf 65536

typedef struct Ask{
    int pos;
    int x;
}Ask;

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

    while (x > 0){
        s[cnt++] = x % 10 + '0';
        x /= 10;
    }

    while (cnt > 0)
        putCharFast(s[--cnt]);
}

int cmp(const void* a, const void* b){
    int x = *(int*)a;
    int y = *(int*)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

int findPos(int* b, int n, int x){
    int l = 1;
    int r = n;

    while (l <= r){
        int m = (l + r) / 2;

        if (b[m] == x)
            return m;

        if (b[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}

void add(int* t, int n, int pos, int x){
    while (pos <= n){
        t[pos] += x;
        pos += pos & -pos;
    }
}

int sum(int* t, int pos){
    int res = 0;

    while (pos > 0){
        res += t[pos];
        pos -= pos & -pos;
    }

    return res;
}

int main(){
    int n = getInt();
    int m = getInt();

    int* a = (int*)malloc((n + 1) * sizeof(int));
    int* b = (int*)malloc((n + m + 1) * sizeof(int));
    int* t = (int*)calloc((n + m + 1), sizeof(int));
    Ask* q = (Ask*)malloc((m + 1) * sizeof(Ask));

    int cnt = 0;

    for (int i = 1; i <= n; i++){
        a[i] = getInt();
        cnt++;
        b[cnt] = a[i];
    }

    for (int i = 1; i <= m; i++){
        q[i].pos = getInt();
        q[i].x = getInt();
        cnt++;
        b[cnt] = q[i].x;
    }

    qsort(b + 1, cnt, sizeof(int), cmp);

    int k = 1;
    for (int i = 2; i <= cnt; i++){
        if (b[i] != b[k]){
            k++;
            b[k] = b[i];
        }
    }

    for (int i = 1; i <= n; i++){
        int p = findPos(b, k, a[i]);
        add(t, k, p, 1);
    }

    for (int i = 1; i <= m; i++){
        int pos = q[i].pos;
        int x = q[i].x;

        add(t, k, findPos(b, k, a[pos]), -1);
        a[pos] = x;
        add(t, k, findPos(b, k, a[pos]), 1);

        putInt(sum(t, findPos(b, k, x)));
        putCharFast('\n');
    }

    flush();
    return 0;
}
