#include <stdio.h> // Подключение библиотеки ввода-вывода
#include <string.h> // Подключение библиотеки для работы со строками

#define MAX_WORDS 1000 // Максимальное количество слов в словаре
#define MAX_WORD_LEN 50 // Максимальная длина слова

struct dict_entry { // Определение структуры для хранения слов и их переводов
    char word[MAX_WORD_LEN];
    char translation[MAX_WORD_LEN];
};

int main() { // Главная функция программы
    FILE *input_file, *output_file; // Указатели на входной и выходной файлы
    char input_filename[] = "source.txt"; // Имя входного файла
    char output_filename[] = "output.txt"; // Имя выходного файла
    char line[1000]; // Буфер для хранения строки из входного файла
    int i, n, found; // Переменные для циклов и поиска слов
    struct dict_entry dict[MAX_WORDS]; // Массив для хранения словаря
    int freq[MAX_WORDS] = {0}; // Массив для хранения частоты встречаемости слов

    // Определение словаря
    struct dict_entry dict_init[] = {
        {"тирг", "tirg"},
        {"взор", "vzor"}
    };
    n = sizeof(dict_init) / sizeof(dict_init[0]); // Количество слов в словаре
    for (i = 0; i < n; i++) {
        dict[i] = dict_init[i]; // Копирование слов из исходного словаря в массив словаря
    }

    input_file = fopen(input_filename, "r"); // Открытие входного файла
    if (input_file == NULL) { // Проверка на ошибку открытия файла
        printf("Error opening input file\n"); // Вывод сообщения об ошибке
        return 1; // Возврат кода ошибки
    }

    output_file = fopen(output_filename, "w"); // Открытие выходного файла
    if (output_file == NULL) { // Проверка на ошибку открытия файла
        printf("Error opening output file\n"); // Вывод сообщения об ошибке
        return 1; // Возврат кода ошибки
    }

    while (fgets(line, sizeof(line), input_file)) { // Чтение входного файла построчно
        char *token = strtok(line, " ,.-\n"); // Разбиение строки на слова и разделители
        while (token != NULL) {
            if (strchr(" ,.-\n", token[strlen(token) - 1])) { // Проверка, является ли токен разделителем
                fputs(token, output_file); // Если токен - разделитель, записываем его в выходной файл
            } else {
                found = 0;
                for (i = 0; i < n; i++) {
                    if (strcmp(token, dict[i].word) == 0) { // Поиск слова в словаре
                        fprintf(output_file, "%s ", dict[i].translation); // Замена слова на перевод
                        freq[i]++; // Увеличение частоты встречаемости слова
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    fputs(token, output_file); // Если слово не найдено в словаре, записываем его в выходной файл
                }
            }
            token = strtok(NULL, " ,.-\n"); // Получение следующего токена
        }
    }

    fclose(input_file); // Закрытие входного файла
    fclose(output_file); // Закрытие выходного файла

    return 0; // Возврат кода успешного завершения программы
}
