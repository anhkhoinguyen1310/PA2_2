#include "file_handler.h"
#include "spell_check.h"
#include <stdio.h>
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
    // Placeholder for function that reads and processes the file
    // This function should open the file, read its contents,
    // and check each word's spelling.
    printf("Processing file: %s\n", filePath);
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
