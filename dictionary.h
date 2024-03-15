#ifndef DICTIONARY_H
#define DICTIONARY_H

#define WORD_MAX_LENGTH 256

int loadDictionary(const char* path);
int isWordInDictionary(const char* word);
void unloadDictionary();

#endif
