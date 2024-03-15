#include "file_handler.h"
#include "spell_check.h"
#include <stdio.h>
#include <ctype.h> 
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void checkSpelling(const char *path);

// Helper function to determine if a path is a directory
int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) return 0;
    return S_ISDIR(statbuf.st_mode);
}

// Process a single file
void processFile(const char *filePath) {
    printf("Processing file: %s\n", filePath);

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
        int wordPos = 1;

        while (*start) {
            // Skip leading delimiters
            while (*start && !isalpha((unsigned char)*start)) {
                start++;
                wordPos++;
            }

            if (!*start) break; // End of line

            end = start;

            while (*end && isalpha((unsigned char)*end)) {
                end++;
            }

            int wordLength = end - start;

            if (wordLength > 0) {
                char word[256]; 
                memcpy(word, start, wordLength);
                word[wordLength] = '\0'; 

                spellCheckWord(word, filePath, lineNum, wordPos);
            }

            wordPos += wordLength;
            if (*end) {
                end++;
                wordPos++; // Skip the delimiter
            }
            start = end;
        }
    }

    fclose(file);
}

// Function to traverse directories and find .txt files
void traverseDirectory(const char *directoryPath) {
    DIR *dir = opendir(directoryPath);
    if (dir == NULL) {
        fprintf(stderr, "Error: Unable to open directory %s\n", directoryPath);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char fullPath[1024];
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; // Skip the current and parent directory entries
        }

        snprintf(fullPath, sizeof(fullPath), "%s/%s", directoryPath, entry->d_name);

        if (isDirectory(fullPath)) {
            traverseDirectory(fullPath); // Recursive call for directories
        } else {
            // Check if the file is a .txt file
            if (strstr(entry->d_name, ".txt") != NULL) {
                processFile(fullPath); // Process .txt files
            }
        }
    }

    closedir(dir);
}

void checkSpelling(const char *path) {
    if (isDirectory(path)) {
        traverseDirectory(path);
    } else {
        processFile(path);
    }
}
