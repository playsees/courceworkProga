#include <stdio.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 50

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
    int i, j, n, found;
    struct dict_entry dict[MAX_WORDS];
    int freq[MAX_WORDS] = {0};

    // Define dictionary
    struct dict_entry dict_init[] = {
        {"тирг", "tirg"},
        {"взор", "vzor"}
    };
    n = sizeof(dict_init) / sizeof(dict_init[0]);
    for (i = 0; i < n; i++) {
        dict[i] = dict_init[i];
    }

    // Open input file
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    // Open output file
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Error opening output file\n");
        return 1;
    }

    // Read input file line by line
while (fgets(line, sizeof(line), input_file)) {
// Split line into words and delimiters
char *token = strtok(line, " ,.-\n");
while (token != NULL) {
// Check if the token is a delimiter
if (strchr(" ,.-\n", token[strlen(token) - 1])) {
// Token is a delimiter, just write it to the output file
fprintf(output_file, "%s", token);
} else {
// Token is a word, search for it in the dictionary
found = 0;
for (i = 0; i < n; i++) {
if (strcmp(token, dict[i].word) == 0) {
// Word found in dictionary, replace with translation
fprintf(output_file, "%s", dict[i].translation);
freq[i]++;
found = 1;
break;
}
}
if (!found) {
// Word not found in dictionary, keep the original word
fprintf(output_file, "%s", token);
}
}
// Get the next token
token = strtok(NULL, " ,.-\n");
}
}
    // Close files
    fclose(input_file);
    fclose(output_file);

    return 0;
}
