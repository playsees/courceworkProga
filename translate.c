#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 100

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: translate <source_file> <dict_file> <output_file>\n");
        return 1;
    }

    // Открытие файлов
    FILE *source_file = fopen(argv[1], "r");
    FILE *dict_file = fopen(argv[2], "r");
    FILE *output_file = fopen(argv[3], "w");

    if (source_file == NULL || dict_file == NULL || output_file == NULL) {
        printf("Error: could not open file\n");
        return 1;
    }

    // Чтение словаря
    char source_word[MAX_WORD_LEN], target_word[MAX_WORD_LEN];
    int num_words = 0;
    char **source_words = malloc(sizeof(char *));
    char **target_words = malloc(sizeof(char *));
    while (fscanf(dict_file, "%s %s", source_word, target_word) == 2) {
        num_words++;
        source_words = realloc(source_words, num_words * sizeof(char *));
        target_words = realloc(target_words, num_words * sizeof(char *));
        source_words[num_words - 1] = strdup(source_word);
        target_words[num_words - 1] = strdup(target_word);
    }

    // Чтение исходного текста и перевод
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, source_file)) != -1) {
        // Сохранение количества пробелов в начале строки
        int num_spaces = strspn(line, " ");

        char *word = strtok(line, " \n");
        while (word != NULL) {
            int found = 0;
            for (int i = 0; i < num_words; i++) {
                if (strcmp(word, source_words[i]) == 0) {
                    // Добавление пробелов в начало строки переведенного текста
                    for (int j = 0; j < num_spaces; j++) {
                        fprintf(output_file, " ");
                    }
                    fprintf(output_file, "%s ", target_words[i]);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                // Добавление пробелов в начало строки переведенного текста
                for (int j = 0; j < num_spaces; j++) {
                    fprintf(output_file, " ");
                }
                fprintf(output_file, "%s ", word);
            }
            word = strtok(NULL, " \n");
        }
        fprintf(output_file, "\n");
    }

    // Освобождение памяти и закрытие файлов
    for (int i = 0; i < num_words; i++) {
        free(source_words[i]);
        free(target_words[i]);
    }
    free(source_words);
    free(target_words);
    free(line);
    fclose(source_file);
    fclose(dict_file);
    fclose(output_file);

    return 0;
}
