#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50
#define MAX_DEFINITION_LENGTH 200

typedef struct {
    char word[MAX_WORD_LENGTH];
    char definition[MAX_DEFINITION_LENGTH];
} DictionaryEntry;

DictionaryEntry dictionary[MAX_WORDS] = {
    {"apple", "A fruit that is typically red, green, or yellow."},
    {"banana", "A long curved fruit that grows in clusters and has soft pulpy flesh and yellow skin when ripe."},
    {"cat", "A small domesticated carnivorous mammal with soft fur, a short snout, and retractile claws."},
    {"dog", "A domesticated carnivorous mammal that typically has a long snout, an acute sense of smell, non-retractable claws, and a barking, howling, or whining voice."},
    {"elephant", "A large herbivorous mammal with a trunk, native to Africa and southern Asia."}
};

int wordCount = 5;

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
}

int main() {
    int choice;
    char word[MAX_WORD_LENGTH];
    char definition[MAX_DEFINITION_LENGTH];

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
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
