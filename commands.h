#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct wList{
    char *word; //the stored word
    int wordLenght; //lenght of the word in letters
    int uniqLetters; //number of unique words in letter
    int numOfTimes; //number of time a word appears in the text 
    int insertionMode; //0 from fille, 1 from keyboard
    char insertionDate[11];
    char insertionTime[9];
    struct wList *next; //pointers for the list
    struct wList *previous; //same 
}wordList;

extern wordList *head; //global variable for the head of the list

void insert(char *user_input);
void load(char *user_input);
void create(char *user_input);
void showfwd(char *user_input);
void showrev(char *user_input);
void findfwd(char *user_input);
void findrev(char *user_input);
void save(char *user_input);
wordList *delete(wordList *head, char *user_input);
void print_word(char *user_input);
int word_is_valid(char *token);
wordList* create_new_node(char *token);
void insert_alphabetically(wordList *new_node);
int wordLenght(char *token);
int uniqLetters(char *token);
void numOfTimes(wordList *found);
wordList *find_word(char *token);
int difficulty(wordList *d);
void free_memory(void);

#endif