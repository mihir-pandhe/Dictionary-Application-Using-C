#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50
#define MAX_DEFINITION_LENGTH 200
#define DICTIONARY_FILE "dictionary.txt"

typedef struct {
    char word[MAX_WORD_LENGTH];
    char definition[MAX_DEFINITION_LENGTH];
} DictionaryEntry;

DictionaryEntry dictionary[MAX_WORDS];
int wordCount = 0;

void loadDictionary() {
    FILE *file = fopen(DICTIONARY_FILE, "r");
    if (file == NULL) {
        printf("No dictionary file found. Starting with an empty dictionary.\n");
        return;
    }

    while (fscanf(file, "%s %[^\n]", dictionary[wordCount].word, dictionary[wordCount].definition) != EOF) {
        wordCount++;
    }

    fclose(file);
}

void saveDictionary() {
    FILE *file = fopen(DICTIONARY_FILE, "w");
    if (file == NULL) {
        printf("Error saving dictionary.\n");
        return;
    }

    for (int i = 0; i < wordCount; i++) {
        fprintf(file, "%s %s\n", dictionary[i].word, dictionary[i].definition);
    }

    fclose(file);
}

void lookupWord(char *word) {
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(dictionary[i].word, word) == 0) {
            printf("Definition: %s\n", dictionary[i].definition);
            return;
        }
    }
    printf("Word not found in dictionary.\n");
}

void addWord(char *word, char *definition) {
    if (wordCount >= MAX_WORDS) {
        printf("Dictionary is full. Cannot add more words.\n");
        return;
    }
    strcpy(dictionary[wordCount].word, word);
    strcpy(dictionary[wordCount].definition, definition);
    wordCount++;
    printf("Word added successfully.\n");
    saveDictionary();
}

int main() {
    int choice;
    char word[MAX_WORD_LENGTH];
    char definition[MAX_DEFINITION_LENGTH];

    loadDictionary();

    while (1) {
        printf("1. Look up word\n2. Add word\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter a word to look up: ");
                scanf("%s", word);
                lookupWord(word);
                break;
            case 2:
                printf("Enter the word: ");
                scanf("%s", word);
                getchar();
                printf("Enter the definition: ");
                fgets(definition, MAX_DEFINITION_LENGTH, stdin);
                definition[strcspn(definition, "\n")] = '\0';
                addWord(word, definition);
                break;
            case 3:
                saveDictionary();
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
