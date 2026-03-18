#include <stdio.h>

void print_hex_file(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("Не удалось открыть файл");
        return;
    }
    
    unsigned char byte;
    int count = 0;
    int line_count = 0;
    
    printf("%20s\n", filename);
    printf("----------------------------------------------------\n");
    
    while (fread(&byte, sizeof(unsigned char), 1, f)) {
        printf("%02X ", byte);
        count++;
        
        // Новая строка каждые 16 байт
        if (count % 16 == 0) {
            printf("\n");
            line_count++;
            
            // Добавляем пустую строку между блоками
            if (line_count % 3 == 0) {
                printf("\n");
            }
        }
    }
    
    // Если последняя строка неполная
    if (count % 16 != 0) {
        printf("\n");
    }
    
    printf("\n");
    fclose(f);
}

int main() {
    print_hex_file("input.bin");
    print_hex_file("output.bin");
    return 0;
}