#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libstemmer.h>

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
    int c;
    while ((c = fgetc(source_file)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            // Просто записываем пробелы, табуляции и переносы строк в выходной файл
            fputc(c, output_file);
        } else {
            // Считываем слово из исходного файла
            char word[MAX_WORD_LEN];
            int i = 0;
            while (c != EOF && c != ' ' && c != '\n' && c != '\t') {
                word[i++] = c;
                c = fgetc(source_file);
            }
            word[i] = '\0';

            // Ищем перевод слова в словаре
            int found = 0;
            for (int i = 0; i < num_words; i++) {
                if (strcmp(word, source_words[i]) == 0) {
                    fprintf(output_file, "%s", target_words[i]);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                fprintf(output_file, "%s", word);
            }

            // Записываем пробел после слова, если это не конец строки
            if (c != '\n') {
                fputc(' ', output_file);
            }
        }
    }

    // Освобождение памяти и закрытие файлов
    for (int i = 0; i < num_words; i++) {
        free(source_words[i]);
        free(target_words[i]);
    }
    free(source_words);
    free(target_words);
    fclose(source_file);
    fclose(dict_file);
    fclose(output_file);

    return 0;
}
