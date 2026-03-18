#include <stdio.h>
#include <stdlib.h>

#define table_size 1000003 

typedef struct{
    unsigned key; //Само число, значение, ключ
    struct Node *next; //указатель на следующий узел в цепочке
}Node;

typedef struct{
    Node *table[table_size]; //указатель на массив узлов в цепочке
}Hashtable;

unsigned int hash(unsigned int key){
    return (key % table_size); //получаем индекс в таблице
}

void create_hastable(Hashtable *ht){
    for (int i = 0; i < table_size; i++)
        ht->table[i] = NULL; //обнуляем чтобы не было мусора   
}

int add(Hashtable *ht, int key, int *result, int *size){ //добавляет уникальный из таблицы и выводим в result
    unsigned int index = hash(key); //получет индекс
    Node *current = ht->table[index]; //создаем текущую таблицу

    while(current != NULL){//идем до нулла
        if (current->key == key)
            return 0; //уже есть такой ключ не добавляем 
        
        current = current->next;
    }   

    Node *new = (Node*)calloc(1, sizeof(Node));
    new->key = key;
    new->next = ht->table[index];
}
