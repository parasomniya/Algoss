#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define table_size 100000

typedef struct ActorBio{
    char name[31];
    int birthYear;
    char country[11]; 
}ActorBio;

typedef struct ActorInMovie{
    char actorName[31];
    char movieName[21];
}ActorInMovie;

// typedef struct joined{
//     char name[31];
//     int birthYear;
//     char country[11]; 
//     char actorName[31];
//     char movieName[21];
// }joined;


void sqlJoin(ActorBio A[table_size], ActorInMovie B[table_size], int N, int M, FILE *output){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (strcmp(A[i].name, B[j].actorName) == 0){
                fprintf(output, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n", 
                        A[i].name, 
                        A[i].birthYear, 
                        A[i].country, 
                        B[j].actorName, 
                        B[j].movieName);
            }
        }
    }
    
    return;
}

int main(){
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    ActorBio A[table_size];
    ActorInMovie B[table_size];
    int N, M;
    
    fscanf(input, "%d", &N);
    
    for (int i = 0; i < N; i++){
        fscanf(input, " \"%[^\"]\" %d \"%[^\"]\"\n", 
               A[i].name, &A[i].birthYear, A[i].country);
    }
    
    fscanf(input, "%d", &M);
    
    for (int i = 0; i < M; i++){
        fscanf(input, " \"%[^\"]\" \"%[^\"]\"\n", 
               B[i].actorName, B[i].movieName);
    }
    
    sqlJoin(A, B, N, M, output);
    
    fclose(input);
    fclose(output);
    return 0;
}