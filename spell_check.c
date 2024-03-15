#include "spell_check.h"
#include "dictionary.h"
#include "error_report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper function to check if a character is considered a delimiter
int isDelimiter(char character) {
    return !isalpha(character) && character != '-'; // Include hyphen for words like "spell-check"
}

// Function to process a single word for spell-checking
void spellCheckWord(const char* word, const char* filePath, int lineNum, int wordPos) {
    if (!isWordInDictionary(word)) {
        reportError(filePath, lineNum, wordPos, word);
    }
}

// Function to process the content of a file and spell-check it
void spellCheckFile(const char *filePath) {
    printf("Opening file for spell checking: %s\n", filePath);
    FILE *file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filePath);
        return;
    }

    char line[1024];
    int lineNum = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        lineNum++;
        char *start = line;
        char *end = NULL;
        int wordPos = 1; // Start position of the first word

        while (*start) {
            // Skip leading delimiters to find the start of a word
            while (*start && isDelimiter(*start)) {
                start++;
                wordPos++;
            }
            if (!*start) break; // End of line

            // Find the end of the current word
            end = start;
            while (*end && !isDelimiter(*end)) {
                end++;
            }

            // Extract the word
            int wordLength = end - start;
            if (wordLength > 0) {
                char word[256]; // Assuming no word exceeds 255 characters
                memcpy(word, start, wordLength);
                word[wordLength] = '\0'; // Null-terminate the word

                // Spell-check the word
                spellCheckWord(word, filePath, lineNum, wordPos);
            }

            // Update start and wordPos for the next word
            wordPos += wordLength + 1; // +1 for the delimiter
            start = end;
        }
    }

    fclose(file);
}
