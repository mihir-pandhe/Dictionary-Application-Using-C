#include <stdio.h>
#include <string.h>

#define MAX_WORDS 5
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

void lookupWord(char *word) {
    for (int i = 0; i < MAX_WORDS; i++) {
        if (strcmp(dictionary[i].word, word) == 0) {
            printf("Definition: %s\n", dictionary[i].definition);
            return;
        }
    }
    printf("Word not found in dictionary.\n");
}

int main() {
    char word[MAX_WORD_LENGTH];
    printf("Enter a word to look up: ");
    scanf("%s", word);
    lookupWord(word);
    return 0;
}
