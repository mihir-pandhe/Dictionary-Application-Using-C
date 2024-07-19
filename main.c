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

    while (fscanf(file, "%49s %[^\n]", dictionary[wordCount].word, dictionary[wordCount].definition) != EOF) {
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

void lookupWord(const char *word) {
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(dictionary[i].word, word) == 0) {
            printf("Definition: %s\n", dictionary[i].definition);
            return;
        }
    }
    printf("Word not found in dictionary.\n");
}

void addWord(const char *word, const char *definition) {
    if (wordCount >= MAX_WORDS) {
        printf("Dictionary is full. Cannot add more words.\n");
        return;
    }
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(dictionary[i].word, word) == 0) {
            printf("Word already exists in dictionary.\n");
            return;
        }
    }
    strncpy(dictionary[wordCount].word, word, MAX_WORD_LENGTH - 1);
    strncpy(dictionary[wordCount].definition, definition, MAX_DEFINITION_LENGTH - 1);
    wordCount++;
    printf("Word added successfully.\n");
    saveDictionary();
}

void deleteWord(const char *word) {
    int found = 0;
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(dictionary[i].word, word) == 0) {
            found = 1;
            for (int j = i; j < wordCount - 1; j++) {
                dictionary[j] = dictionary[j + 1];
            }
            wordCount--;
            printf("Word deleted successfully.\n");
            saveDictionary();
            return;
        }
    }
    if (!found) {
        printf("Word not found in dictionary.\n");
    }
}

int main() {
    int choice;
    char word[MAX_WORD_LENGTH];
    char definition[MAX_DEFINITION_LENGTH];

    loadDictionary();

    while (1) {
        printf("1. Look up word\n2. Add word\n3. Delete word\n4. Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting...\n");
            return 1;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Enter a word to look up: ");
                if (scanf("%49s", word) != 1) {
                    printf("Invalid input. Exiting...\n");
                    return 1;
                }
                lookupWord(word);
                break;
            case 2:
                printf("Enter the word: ");
                if (scanf("%49s", word) != 1) {
                    printf("Invalid input. Exiting...\n");
                    return 1;
                }
                getchar();
                printf("Enter the definition: ");
                if (fgets(definition, MAX_DEFINITION_LENGTH, stdin) == NULL) {
                    printf("Error reading definition. Exiting...\n");
                    return 1;
                }
                definition[strcspn(definition, "\n")] = '\0';
                addWord(word, definition);
                break;
            case 3:
                printf("Enter the word to delete: ");
                if (scanf("%49s", word) != 1) {
                    printf("Invalid input. Exiting...\n");
                    return 1;
                }
                deleteWord(word);
                break;
            case 4:
                saveDictionary();
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
