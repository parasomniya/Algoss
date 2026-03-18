#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct list{
    long long digit;
    struct list *next;
};

typedef struct Stack{
    struct list *top;
}Stack;

bool empty(Stack *S){
    return (S->top == NULL);
}

void create_stack(Stack **S){
    *S = (Stack *)calloc(1, sizeof(Stack));
    (*S)->top = NULL;
}

long long pop(Stack *S){
    struct list *p = S->top;
    long long a = p->digit;
    S->top = p->next;
    free(p);
    return a;
}

void push(Stack *S, long long a){
    struct list *p = (struct list*)calloc(1, sizeof(struct list));
    p->digit = a;
    p->next = S->top;
    S->top = p;
}

bool isOperator(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int main(){
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    char *string = (char*)calloc(2001, sizeof(char));
    if (!fgets(string, 2001, input)) {
        fprintf(output, "0\n");
        fclose(input);
        fclose(output);
        return 0;
    }

    Stack *stack;
    create_stack(&stack);

    int len = strlen(string);
    int i = 0;
    
    while (i < len){
        while (i < len && isspace(string[i])){
            i++;
        }
        
        if (i >= len) break;

        char token = string[i];

        if (isdigit(token) || (token == '-' && i + 1 < len && isdigit(string[i + 1]))){
            int sign = 1;
            if (token == '-'){
                sign = -1;
                i++;
            }
            
            long long num = 0;
            while (i < len && isdigit(string[i])){
                num = num * 10 + (string[i] - '0');
                i++;
            }
            push(stack, sign * num);
        }
        else if (isOperator(token)){
            
            long long a = pop(stack);
            long long b = pop(stack);
            
            long long result = 0;
            if (token == '+') result = b + a;
            else if (token == '-') result = b - a;
            else if (token == '*') result = b * a;
            else if (token == '/') result = b / a;
            
            
            push(stack, result);
            i++;
        }
        else
            i++;
    
    }

    if (empty(stack)){
        fprintf(output, "0\n");
    } 
    else{
        long long result = pop(stack);
        fprintf(output, "%lld\n", result);
    }

    fclose(input);
    fclose(output);
    return 0;
}