//fscanf strtok 
//strstr - ищет первое вхождение подстроки str 2 в str 1
//функция выделения подстроки через стрстр
//for fgets 
//strtok по " "
//strtod
/*
    Если токен содержит "^N" → извлекает константу для экспоненты
    Если токен содержит "N^" (но не содержит "log") → извлекает степень полинома
    Если токен содержит "N" (но не содержит "log") → устанавливает степень полинома = 1.0
    Если токен содержит "logN^" → извлекает степень логарифма
    Если токен содержит "logN" → устанавливает степень логарифма = 1.0
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool substractingString(const char *str, const char *substr){
    return(strstr(str, substr) != NULL);
}

int main(){
    FILE *input = fopen("input.txt", "r");
    freopen("output.txt", "w", stdout);

    int Q = 0;
    fscanf(input, "%d", &Q);

    char string[10000];
    
    double  prev_p = 0.0, 
            prev_s = 0.0,
            prev_l = 0.0;

    for(int i = 0; i <= 2 * Q; i++){

        double  p = 0.0, 
                s = 0.0,
                l = 0.0;

        fgets(string, sizeof(string), input);

        char *buf = strtok(string, " ");
        while (buf != NULL){

            if (substractingString(buf, "^N")){
                char *ptr;
                buf[strlen(buf) - 1] = ' ';
                buf[strlen(buf) - 2] = ' ';
                p = strtod(buf, &ptr);
            }

            if (substractingString(buf, "N^") && substractingString(buf, "log") == 0){
                char *ptr;
                buf[0] = ' ';
                buf[1] = ' ';
                s = strtod(buf, &ptr);
            }
            
            else if (substractingString(buf, "N") && substractingString(buf, "log") == 0){
                char *ptr;
                s = 1;
            }
            
            if (substractingString(buf, "logN^")){
                char *ptr;
                buf[0] = ' ';
                buf[1] = ' ';
                buf[2] = ' ';
                buf[3] = ' ';
                buf[4] = ' ';
                
                l = strtod(buf, &ptr);
            }

            else if (substractingString(buf, "logN")){
                l = 1;
            }

            buf = strtok(NULL, " ");
        }

        p = (p == 1.0) ? 0.0 : p;
        
        if (i%2 == 0 && i > 0){

            if (p > prev_p)
                printf("%d\n", -1);  // Первая асимптотика меньше
                
            else if (p < prev_p)
                printf("%d\n", 1); // Первая асимптотика больше
    
            else{

                if (s > prev_s)
                    printf("%d\n", -1);  // Первая асимптотика меньше
                    
                else if (s < prev_s)
                    printf("%d\n", 1); // Первая асимптотика больше
                    
                else{
                    if (l > prev_l)
                        printf("%d\n", -1);  // Первая асимптотика меньше
                    
                    else if (l < prev_l)
                        printf("%d\n", 1); // Первая асимптотика больше
                        
                    else
                        printf("%d\n", 0);  // Асимптотики равны

                    }
                }
            }

            prev_p = p; 
            prev_s = s;
            prev_l = l;

        }

    fclose(input);
    return 0;
}