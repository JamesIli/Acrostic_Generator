#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "commands.h"

extern wordList *head;
char save_acrostic[100] = "";

void insert(char *user_input){
   char *token = strtok(user_input, " "); //uses strtoken to split the string into parts named token (strtok = MVP btw)
    while(token != NULL){
        if(word_is_valid(token) == 1){ //if the word is indeed a word
            int i; 
            for(i = 0; token[i]; i++){
                token[i] = toupper(token[i]);
            }
            wordList *found = find_word(token); //checks if the word was already saved
            if(found != NULL){
                numOfTimes(found);
                printf("'%s' already was inserted. This was the %d time\n", token, found->numOfTimes);
            }
            else{
                wordList *new_node = create_new_node(token);
                insert_alphabetically(new_node);
                printf("Inserted '%s'. The lenght is: %d. The unique letters are: %d\n", token, new_node->wordLenght, new_node->uniqLetters);   
                printf("These words were inserted in: ");
                printf("Date:%s || Time:%s\n", new_node->insertionDate, new_node->insertionTime);
            }
        }
        else{
            printf("Invalid word: %s\n", token);
        }
        token = strtok(NULL, " ");
        
    }
}

void load(char *user_input){
    char file_name[10000];
    snprintf(file_name, sizeof(file_name), "%s.txt", user_input); //add the txt
    FILE *fp = fopen(file_name, "r");
    if(!fp){
        printf("Could not open the file:%s\n", file_name);
    }
    else{
        char line[10000];
        while(fgets(line, sizeof(line), fp) != NULL){
            char *token = strtok(line, " \n\r\t");
            while(token != NULL){
                if(word_is_valid(token) == 1){ //if word is valid
                    if(strlen(token) <= 1){
                        printf("Skipped one letter word:'toupper%s' because Mr. Trifonopoulos said so\n", token);
                    }
                    else{
                        int i; 
                        for(i = 0; token[i]; i++){
                            token[i] = toupper(token[i]);
                        }
                        wordList *found = find_word(token);
                        if(found != NULL){ //if the word was already saved
                            numOfTimes(found);
                            printf("The word:'%s' already exist. This was the %d time\n" , token, found->numOfTimes);
                        }
                        else{
                            wordList *new_node = create_new_node(token);
                            new_node->insertionMode = 0;
                            insert_alphabetically(new_node);
                            printf("Loaded '%s' from file:%s. The length is: %d. The unique letters are:%d\n", token, file_name, new_node->wordLenght, new_node->uniqLetters);
                        }

                    }
                }
                else{
                    printf("Invalid word: %s\n", token);
                }
                token = strtok(NULL, " \n\r\t");
            }
        }
        fclose(fp);
        printf("Closing %s...\n", file_name);
    }
}

void create(char *user_input){
    char *acrostic = strtok(user_input, " ");
    char *difficulty = strtok(NULL, " ");
    if(acrostic == NULL || difficulty == 0){
        printf("Wrong command(maybe add difficulty?)\n");
    }
    else{
        strncpy(save_acrostic, acrostic, sizeof(save_acrostic)); //saves the acrostic's name for the save function 
        int flagd;
        if(toupper(difficulty[0]) == 'E'){ //easy dif
            flagd = 1;
        }
        else if(toupper(difficulty[0]) == 'H'){ //hard dif
            flagd = 2;
        }
        int len = strlen(acrostic);
        wordList *row[100] = {NULL};
        int i, j;
        for(i = 0; i < len; i++){ // For each letter in the acrostic, find a word starting with that letter
            char letter = toupper(acrostic[i]);
            wordList *matched_words[100];
            int count = 0;
            wordList *currw = head;
            while (currw != NULL){
                if(toupper(currw->word[0]) == letter){
                    int dif_word_check = 0;
                    if(flagd == 1){
                        if(currw->numOfTimes >= 2 && currw->wordLenght <= 5 && currw->uniqLetters <= 4){ //
                            dif_word_check = 1;
                        }
                    }
                    else{
                        if(currw->numOfTimes == 1 && currw->wordLenght >= 7 && currw->uniqLetters >= 5){
                            dif_word_check = 1;
                        }
                    }
                    if(dif_word_check == 1){
                        matched_words[count] = currw;
                        count++;
                    }
                }
                currw = currw->next;
            }
            if(count > 0){
                int r = rand() % count;
                row[i] = matched_words[r];
            }
        }
        printf("\n\033[35mAcrostic:\033[0m\n"); // Print the acrostic: vertical word,horizontal words
        for(j = 0; j < len; j++){
            printf("%c ", toupper(acrostic[j]));
            if(row[j] && row[j]->word){
                print_word(row[j]->word); //unsolved word
                printf("  -->%s\n", row[j]->word); //solved word
            }
            else{
                printf("\n");
            }
        }
    }
}

void showfwd(char *user_input){
    int num_showfwd = atoi(user_input); //makes it so it understands numbers the same logic happenst at most of the following functiions
    if(num_showfwd <= 0){
        printf("Please provide a valid number for the 'showfwd:' command\n");
    }
    else{
        wordList *current = head;
        if(current == NULL){
            printf("The list is empty\n");
        }
        else{
            int count = 0;
            while(current != NULL && count < num_showfwd){
                printf("%d)%s\n",count + 1, current->word);
                current = current->next;
                count++;
            }
        }
    }
}

void showrev(char *user_input){
    int num_showrev = atoi(user_input);
     if(num_showrev <= 0){
        printf("Please provide a valid number for the 'showrev:' command\n");
    }
    else{
        wordList *current = head;
        if(head == NULL){
            printf("The list is empty\n");
        }
        else{
            while(current->next != NULL){
                current = current->next; //goes to the tail
            }
            int count = 0;
            while(current != NULL && count < num_showrev){
                printf("%d)%s\n", count + 1, current->word);
                current = current->previous;
                count++;
            }
        }
    }
}

void findfwd(char *user_input){
    char word_findfwd[100];
    int num_findfwd = 0;
    char *word = strtok(user_input, " ");
    char *num = strtok(NULL, " ");
    if(word == NULL || num == NULL){
        printf("Invalid use of findfwd. Check the: 'if this is your first time playing' section\n");
    }
    else{
        strcpy(word_findfwd, word);
        num_findfwd = atoi(num);
        if(num_findfwd <= 0){
            printf("Please provide a positive value\n");
        }
        else{
            wordList *current = head;
            if(current == NULL){
                printf("The list is empty\n");
            }
            else{
                int count = 0;
                int found = 0;
                while(current != NULL && count < num_findfwd){
                    if(strncmp(current->word,word_findfwd, strlen(word_findfwd)) == 0){ //compares word with word_findfwd 
                        printf("%d)%s\n", count + 1, current->word);
                        count++;
                        found = 1;
                    }
                    current = current->next;
                }
                if(found == 0){
                    printf("No words starting with '%s' were inserted\n", word_findfwd);
                }
            }
        }
    }
}

void findrev(char *user_input){
    char word_findrev[100];
    int num_findrev = 0;
    char *word = strtok(user_input, " ");
    char *num = strtok(NULL, " ");
    if(word == NULL || num == NULL){
        printf("Invalid use of findrev. Check the: 'if this is your first time playing' section\n");
    }
    else{
        strcpy(word_findrev, word);
        num_findrev = atoi(num);
        if(num_findrev <= 0){
            printf("Please provide a positive value\n");
        }
        else{
            wordList *current = head;
            if(current == NULL){
                printf("The list is empty\n");
            }
            else{
                int count = 0;
                int found = 0;
                while(current->next != NULL){
                    current = current->next; //goes to the tail
                }
                while(current != NULL && count < num_findrev){
                    if(strncmp(current->word, word_findrev, strlen(word_findrev)) == 0){
                        printf("%d)%s\n", count + 1, current->word);
                        count++;
                        found = 1;
                    }
                    current = current->previous;
                }
                if(found == 0){
                    printf("No words starting with '%s' were inserted\n", word_findrev);
                }
            }
        }
    }
}

void save(char *user_input){
    if(strlen(save_acrostic) == 0){
        printf("You can't save an acrostic without creating one\n");
    }
    else{
        char save_file[100];
        snprintf(save_file, sizeof(save_file), "%s.txt", user_input); //ads the txt 
        FILE *fp = fopen(save_file, "w");
        if(!fp){
            printf("Could not save ):\n");
        }
        else{
            fprintf(fp, "The last acrostic was:%s\n", save_acrostic);
            fclose(fp);
            printf("Saved the acrostic at %s file\n", save_file);
        }
    }
}

wordList *delete(wordList *head, char *user_input){
    char *token = strtok(user_input, " ");
    while(token != NULL){
        wordList *delete_word = find_word(token);
        if(delete_word != NULL){  //the word exist 
            if(delete_word->previous == NULL && delete_word->next ==NULL){ //if only one node
                free(delete_word->word);
                free(delete_word);
                head = NULL;
                printf("Deleted:%s\n", token);
            }
            else if(delete_word->previous == NULL){ //if in head node
                head = delete_word->next;
                head->previous = NULL;
                free(delete_word->word);
                free(delete_word);
                printf("Deleted:%s\n", token);
            }
            else if(delete_word->next == NULL){ //if in tail node
               delete_word->previous->next = NULL;
                free(delete_word->word);
                free(delete_word);
                printf("Deleted:%s\n", token);
            }
            else{ //if in between
                delete_word->previous->next = delete_word->next;
                delete_word->next->previous = delete_word->previous;
                free(delete_word->word);
                free(delete_word);
                printf("Deleted:%s\n", token);
            }
        }
        else{ //the word isnt inserted
            printf("The word:'%s' is not in the list\n", token);
        }
        token = strtok(NULL, " ");
        

    }
    return head;
}