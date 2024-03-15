#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include "file_handler.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <dictionary_path> <text_file1> [text_file2] ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dictionaryPath = argv[1];

    // Load the dictionary
    if (!loadDictionary(dictionaryPath)) {
        fprintf(stderr, "Failed to load the dictionary from %s\n", dictionaryPath);
        return EXIT_FAILURE;
    }

    // Process each text file or directory given as command-line arguments
    for (int i = 2; i < argc; i++) {
        checkSpelling(argv[i]);
    }

    // Unload the dictionary and cleanup
    unloadDictionary();

    // Program completed successfully
    return EXIT_SUCCESS;
}
