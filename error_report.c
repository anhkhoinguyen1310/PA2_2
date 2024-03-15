#include "error_report.h"
#include <stdio.h>

// Function to report spelling errors
void reportError(const char *filePath, int lineNum, int colNum, const char *word) {
    printf("%s (%d, %d): %s\n", filePath, lineNum, colNum, word);
}
