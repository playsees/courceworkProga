#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 128

int main() {
    // Открытие файлов
    FILE* input_file = fopen("text_rus.txt", "r");
    FILE* dictionary_file = fopen("dictionary.txt", "r");
    FILE* output_file = fopen("text_eng.txt", "w");

    // Чтение словаря
    char dictionary[MAX_WORD_LENGTH][2][MAX_WORD_LENGTH];
    int dictionary_size = 0;
    while (fscanf(dictionary_file, "%s %s", dictionary[dictionary_size][0], dictionary[dictionary_size][1]) == 2) {
        dictionary_size++;
    }

    // Перевод текста
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        char* word = strtok(line, " \t\n");
        while (word != NULL) {
            int found = 0;
            for (int i = 0; i < dictionary_size; i++) {
                if (strcmp(word, dictionary[i][0]) == 0) {
                    fprintf(output_file, "%s ", dictionary[i][1]);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                fprintf(output_file, "%s ", word);
            }
            word = strtok(NULL, " \t\n");
        }
        fprintf(output_file, "\n");
    }

    // Закрытие файлов
    fclose(input_file);
    fclose(dictionary_file);
    fclose(output_file);

    return 0;
}
