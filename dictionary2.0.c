#include <stdio.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 50

// Определяем структуру данных для хранения словаря
struct dict_entry {
    char word[MAX_WORD_LEN];
    char translation[MAX_WORD_LEN];
};

int main() {
    FILE *input_file, *output_file;
    char input_filename[] = "input.txt";
    char output_filename[] = "output.txt";
    char line[1000];
    char *word;
    int i, j, k, n, found;
    struct dict_entry dict[MAX_WORDS];
    int freq[MAX_WORDS] = {0};

    // Определяем словарь статически, используя заданные слова и их переводы
    struct dict_entry dict[] = {
        {"тирг", "tirg"},
        {"взор", "vzor"}
    };
    n = sizeof(dict) / sizeof(dict[0]);

    // Открываем входной файл для чтения и выходной файл для записи
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Error opening input file\n");
        return 1;
    }
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Error opening output file\n");
        return 1;
    }

    // Считываем входной файл построчно и разбиваем каждую строку на слова
    while (fgets(line, sizeof(line), input_file)) {
        word = strtok(line, " ,.-\n");
        while (word != NULL) {
            // Ищем слово в словаре
            found = 0;
            for (i = 0; i < n; i++) {
                if (strcmp(word, dict[i].word) == 0) {
                    // Слово найдено в словаре, заменяем его переводом
                    fprintf(output_file, "%s ", dict[i].translation);
                    freq[i]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                // Слово не найдено в словаре, записываем его без изменений
                fprintf(output_file, "%s ", word);
            }
            word = strtok(NULL, " ,.-\n");
        }
        fprintf(output_file, "\n");
    }

    // Сортируем словарь по частоте появления слов
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (freq[i] < freq[j]) {
                // Меняем местами элементы словаря и частоты
                struct dict_entry temp = dict[i];
                dict[i] = dict[j];
                dict[j] = temp;
                int temp_freq = freq[i];
                freq[i] = freq[j];
                freq[j] = temp_freq;
            }
        }
    }

    // Выводим отсортированный словарь на консоль
    printf("Dictionary:\n");
    for (i = 0; i < n; i++) {
        printf("%s -> %s (%d)\n", dict[i].word, dict[i].translation, freq[i]);
    }

    // Закрываем файлы и завершаем программу
    fclose(input_file);
    fclose(output_file);
    return 0;
}
