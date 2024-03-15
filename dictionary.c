#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char word[WORD_MAX_LENGTH];
    struct Node* left;
    struct Node* right;
} Node;

Node* root = NULL;

Node* newNode(const char* word) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node) {
        strcpy(node->word, word);
        node->left = node->right = NULL;
    }
    return node;
}

void insert(Node** root, const char* word) {
    if (*root == NULL) {
        *root = newNode(word);
    } else if (strcmp(word, (*root)->word) < 0) {
        insert(&((*root)->left), word);
    } else if (strcmp(word, (*root)->word) > 0) {
        insert(&((*root)->right), word);
    }
}

int search(Node* root, const char* word) {
    if (root == NULL) {
        return 0;
    }
    int cmp = strcmp(word, root->word);
    if (cmp < 0) {
        return search(root->left, word);
    } else if (cmp > 0) {
        return search(root->right, word);
    } else {
        return 1;
    }
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int loadDictionary(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        perror("Failed to open dictionary");
        return 0;
    }
    char word[WORD_MAX_LENGTH];
    while (fscanf(file, "%255s", word) == 1) {
        // Convert word to lowercase for uniformity
        for (int i = 0; word[i]; i++) {
            word[i] = tolower(word[i]);
        }
        insert(&root, word);
    }
    fclose(file);
    return 1;
}

int isWordInDictionary(const char* word) {
    char lowercaseWord[WORD_MAX_LENGTH];
    // Convert word to lowercase to match dictionary format
    for (int i = 0; word[i]; i++) {
        lowercaseWord[i] = tolower(word[i]);
    }
    lowercaseWord[strlen(word)] = '\0';
    return search(root, lowercaseWord);
}

void unloadDictionary() {
    freeTree(root);
    root = NULL;
}
