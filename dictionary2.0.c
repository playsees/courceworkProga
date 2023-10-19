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
char line[1000]; // Буфер для хранения строки из входного файла // Указатель на текущее слово
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

// Открытие входного файла
input_file = fopen(input_filename, "r");
if (input_file == NULL) { // Проверка на ошибку открытия файла
printf("Error opening input file\n"); // Вывод сообщения об ошибке
return 1; // Возврат кода ошибки
}

// Открытие выходного файла
output_file = fopen(output_filename, "w");
if (output_file == NULL) { // Проверка на ошибку открытия файла
printf("Error opening output file\n"); // Вывод сообщения об ошибке
return 1; // Возврат кода ошибки
}

// Чтение входного файла построчно

while (fgets(line, sizeof(line), input_file)) {
// Split line into words and delimiters
char *token = strtok(line, " ,.-\n");
while (token != NULL) {
// Check if the token is a delimiter
if (strchr(" ,.-\n", token[strlen(token) - 1])) {
// Token is a delimiter, just write it to the output file
fputs(token, output_file);
} else {
// Token is a word, search for it in the dictionary
found = 0;
for (i = 0; i < n; i++) {
if (strcmp(token, dict[i].word) == 0) {
// Word found in dictionary, replace with translation
fprintf(output_file, "%s ", dict[i].translation); // Добавлен пробел
freq[i]++;
found = 1;
break;
}
}
if (!found) {
// Word not found in dictionary, keep the original word
fputs(token, output_file); // Добавлен пробел
}
}
// Get the next token
token = strtok(NULL, " ,.-\n");
}
}


// Закрытие файлов
fclose(input_file);
fclose(output_file);

return 0; // Возврат кода успешного завершения программы
}
