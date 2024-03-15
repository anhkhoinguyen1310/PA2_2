#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H

// Function declaration for processing a file to spell-check each word it contains.
void spellCheckFile(const char *filePath);

// Function declaration for checking the spelling of a single word.
void spellCheckWord(const char* word, const char* filePath, int lineNum, int wordPos);

#endif
