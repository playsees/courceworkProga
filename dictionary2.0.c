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
        // Write line to output file
        fputs(line, output_file);

        // Parse line into words
        word = strtok(line, " ,.-\n");
        while (word != NULL) {
            // Search for word in dictionary
            found = 0;
            for (i = 0; i < n; i++) {
                if (strcmp(word, dict[i].word) == 0) {
                    // Word found in dictionary, replace with translation
                    fprintf(output_file, "%s ", dict[i].translation);
                    freq[i]++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                // Word not found in dictionary, keep original word
                fprintf(output_file, "%s ", word);
            }
            word = strtok(NULL, " ,.-\n");
        }
    }

    // Sort dictionary by frequency of occurrence
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (freq[i] < freq[j]) {
                // Swap entries
                struct dict_entry temp = dict[i];
                dict[i] = dict[j];
                dict[j] = temp;
                int temp_freq = freq[i];
                freq[i] = freq[j];
                freq[j] = temp_freq;
            }
        }
    }

    // Print sorted dictionary to console
    printf("Dictionary:\n");
    for (i = 0; i < n; i++) {
        printf("%s -> %s (%d)\n", dict[i].word, dict[i].translation, freq[i]);
    }

    // Close files
    fclose(input_file);
    fclose(output_file);

    return 0;
}
