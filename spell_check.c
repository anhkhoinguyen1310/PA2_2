#include "spell_check.h"
#include "dictionary.h"
#include "error_report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper function to check if a character is considered a delimiter
int isDelimiter(char character) {
    return !isalpha(character);
}

// Function to process a single word for spell-checking
void checkWord(const char* word, const char* filePath, int lineNum, int startPos) {
    if (!isWordInDictionary(word)) {
        reportError(filePath, lineNum, startPos, word);
    }
}

// Function to process the content of a file and spell-check it
void processFile(const char *filePath) {
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
        int startPos = 0;

        while (*start) {
            // Skip leading delimiters
            while (*start && isDelimiter(*start)) {
                start++;
                startPos++;
            }
            if (!*start) break; // End of line

            // Find the end of the current word
            end = start;
            while (*end && !isDelimiter(*end)) {
                end++;
            }

            // Extract the word
            char word[256]; // Assuming no word exceeds 255 characters
            int wordLength = end - start;
            if (wordLength < sizeof(word)) {
                memcpy(word, start, wordLength);
                word[wordLength] = '\0'; // Null-terminate the word

                // Spell-check the word
                checkWord(word, filePath, lineNum, startPos + 1);
            }

            // Prepare for the next word
            startPos += wordLength;
            start = end;
        }
    }

    fclose(file);
}
