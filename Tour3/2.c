#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hash_size 200003

typedef struct ActorBio{
    char name[31];
    int birthYear;
    char country[11];
}ActorBio;

typedef struct ActorInMovie{
    char actorName[31];
    char movieName[21];
}ActorInMovie;


typedef struct HashNode{
    ActorBio bio;
    struct HashNode* next;
}HashNode;

unsigned int hash(const char* str){
    unsigned int h = 0;
    while (*str){
        h = h * 31 + (unsigned char)(*str);
        str++;
    }
    return h % hash_size;
}

void hashInsert(HashNode* hashTable[], ActorBio* bio){
    unsigned int h = hash(bio->name);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->bio = *bio;
    node->next = hashTable[h];
    hashTable[h] = node;
}

void findAndJoin(HashNode* hashTable[], const char* actorName, const char* movieName, FILE* output){
    unsigned int h = hash(actorName);
    HashNode* curr = hashTable[h];
    
    while (curr != NULL){
        if (strcmp(curr->bio.name, actorName) == 0){
            fprintf(output, "\"%s\" %d \"%s\" \"%s\" \"%s\"\n",
                    curr->bio.name,
                    curr->bio.birthYear,
                    curr->bio.country,
                    actorName,
                    movieName);
        }
        curr = curr->next;
    }
}

int main(){
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    static HashNode* hashTable[hash_size];
    for (int i = 0; i < hash_size; i++)
        hashTable[i] = NULL;
    
    int N, M;
    
    fscanf(input, "%d", &N);
    for (int i = 0; i < N; i++){
        ActorBio bio;
        fscanf(input, " \"%[^\"]\" %d \"%[^\"]\"\n", 
               bio.name, &bio.birthYear, bio.country);
        hashInsert(hashTable, &bio);
    }
    
    fscanf(input, "%d", &M);
    for (int i = 0; i < M; i++){
        ActorInMovie movie;
        fscanf(input, " \"%[^\"]\" \"%[^\"]\"\n", 
               movie.actorName, movie.movieName);
        
        findAndJoin(hashTable, movie.actorName, movie.movieName, output);
    }
    
    fclose(input);
    fclose(output);
    return 0;
}