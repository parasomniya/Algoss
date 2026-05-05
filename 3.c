#include <stdio.h>

#define sz 505

int a[sz][sz];

int main(){
    int n;
    scanf("%d", &n);

    char s[sz];

    for(int i = 0; i < n; i++){
        scanf("%s", s);
        for(int j = 0; j < n; j++){
            a[i][j] = s[j] - '0';
        }
    }

    for(int i = 0; i < n; i++)
        a[i][i] = 1;

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            if(a[i][k] == 0)
                continue;

            for(int j = 0; j < n; j++){
                if(a[k][j] == 1)
                    a[i][j] = 1;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d", a[i][j]);
        printf("\n");
    }

    return 0;
}
