#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "commands.h"

wordList *head = NULL; //global variable for the head of the list

void Menu(void);
int parse(char *user_input);
void print_word(char *token);

//all other functions are declared in commands.h and get done in .c//

int main(void){
    srand(time(NULL));
    Menu();
    printf("\033[35mPlease give a command\033[0m\n");
    char user_input[100];
    while(1){
        fgets(user_input, sizeof(user_input), stdin);
        parse(user_input);
    }
    return 0;
}

void Menu(void){
    printf("Welcome dear contestant! It's time for\n");
    printf(" \033[35mTTTTTT  H   H  EEEEE     TTTTTT   RRRR   III  FFFFF  OOO    SSSS  H   H  OOO  W   W\033[0m\n");
    printf(" \033[35m  TT    H   H  E           TT     R   R   I   F     O   O  S      H   H O   O W   W\033[0m\n");
    printf(" \033[35m  TT    HHHHH  EEEE        TT     RRRR    I   FFF   O   O   SSS   HHHHH O   O W W W\033[0m\n");
    printf(" \033[35m  TT    H   H  E           TT     R  R    I   F     O   O     S   H   H O   O WW WW\033[0m\n");
    printf(" \033[35m  TT    H   H  EEEEE       TT     R   R  III  F      OOO   SSSS   H   H  OOO  W   W\033[0m\n");
    printf("Press any key: ");
    getchar();
    printf("Welcome to the \033[35mTrifoShow\033[0m\n");
    jump_menu:
    printf("Press 1 to start the game\n");
    printf("Press 2 if this is your first time playing\n");
    printf("Press 3 to view the credits\n");
    int Start_Button;
	do{	
		scanf("%d", &Start_Button);
        while((getchar()) != '\n');
		if(Start_Button != 1 && Start_Button != 2 && Start_Button != 3 && Start_Button != 21){
			printf("Please press either 1 or 2 or 3\n");
		}
	}while(Start_Button != 1 && Start_Button != 2 && Start_Button !=3 && Start_Button != 21);
    if(Start_Button == 2){
        printf("Welcome contestant!\nThis is a game show presented by our host *audience gasps* Christos Trifonopulos!!! *loud cheers from audience*\n");
        printf("Today's game is acrostics!\nThere are two ways to play:\n");
        printf("(1)You add your own words or sentences with the command \033[1minsert:\033[0m followed by the words or sentances\n");
        printf("(2)You ask Mr Trifonopoulos to give you words by using his broad knowledge with the command \033[1mload:\033[0m followed by the category's name\n");
        printf("After your inputs start the acrostic puzzle with the command \033[1mcreate:\033[0m followed by the acrostic word and desired difficulty\n");
        printf("There are more commands you could use\nDo you wish for some more explanation?\nPress 1 if Yes\nPress 2 if No\n");
        int Command_Tutorial;
        do{	
		    scanf("%d", &Command_Tutorial);
            while((getchar()) != '\n');
		    if(Command_Tutorial != 1 && Command_Tutorial != 2){
		    	printf("Please press either 1 or 2\n");
		    }
        }while(Command_Tutorial != 1 && Command_Tutorial != 2);
        if(Command_Tutorial == 1){
            printf("Command \033[1mdelete:\033[0m\n");
            printf("With this command you can delete any word saved for the acrostic puzzle\n");
            printf("Command \033[1mshowfwd:\033[0m and 033[1mshowrev:\033[0m\n");
            printf("With these commands you can see all the words that have been saved in alphabetical order and in reversed order, respectively\n");
            printf("Command \033[1mfindfwd:\033[0m and \033[1mfindrev:\033[0m followed by an (A) acronym and a (N) number\n");
            printf("With these commands you can find the first (N) words saved that start with the (S) acronym n alphabetical order and in reversed oreder respectively\n");
            printf("Command \033[1msave:\033[0m followed by a name of your choice\n");
            printf("With this command you will save the acrostic and its solution in a txt fille with the name you have given\n");
        }
    }
    if(Start_Button == 21){
        int i;
        for(i=0; i<10000; i++){
            printf("\033[33mAEK \033[0m"); //very important part of code
            if(i%30 == 0){
                printf("\n");
            }
        }
        exit(0);
    }
    if(Start_Button == 3){
        printf("Presented by Christos Trifonopoulos \nProduced by Raptopoulou Studios\nSpecial thanks to Tselikas&Co\n");
        printf("Code made by JamesIli and Dio\n");
        printf("\033[32m(C) 2025 TheTrifoShow. All rights reserved\033[0m\n");
        goto jump_menu;
    }
    printf("If you wish to give up input the command \033[1mexit\033[0m\n");
    printf("Note that there is a 10.000 word limit per inmput :)\n");
    printf("Make sure your Caps Lock is on\n");
}

int parse(char *user_input){
    int len = strlen(user_input);
    if(user_input[len-1] == '\n'){ //removes \n so life becomes easier
        user_input[len-1] = '\0';
    }
    if(strncmp(user_input, "insert:", 7) == 0){ //so it wont save the word insert: the same logic follows for all other commands
        insert(user_input + 7); 
        printf("\033[35mPlease give a command\033[0m\n");
        return 0;
    }
    else if(strncmp(user_input, "load:", 5) == 0){
        load(user_input + 5); 
        printf("\033[35mPlease give a command\033[0m\n");
        return 0;
    }
    else if(strncmp(user_input, "create:", 7) == 0){
        create(user_input + 7);
        printf("\033[35mPlease give a command\033[0m\n");
        return 0;
    }
    else if(strncmp(user_input, "delete:", 7) == 0){
        head = delete(head, user_input + 7);
        printf("\033[35mPlease give a command\033[0m\n");
        return 0;
    }
    else if(strncmp(user_input, "showfwd:", 8) == 0){
        showfwd(user_input + 8);
        printf("\033[35mPlease give a command\033[0m\n");
        return 0;
    }
    else if(strncmp(user_input, "showrev:", 8) == 0){
        showrev(user_input + 8);
        printf("\033[35mPlease give a command\033[0m\n");
        return 0;
    }
    else if(strncmp(user_input, "findfwd:", 8) == 0){
        findfwd(user_input + 8);
        printf("\033[35mPlease give a command\033[0m\n");
        return 0;
    }
    else if(strncmp(user_input, "findrev:", 8) == 0){
        findrev(user_input + 8);
        printf("\033[35mPlease give a command\033[0m\n");
        return 0;
    }
    else if(strncmp(user_input, "save:", 5) == 0){
        save(user_input + 5);
        printf("\033[35mPlease give a command\033[0m\n");
        return 0;
    }
    else if(strcmp(user_input, "exit") == 0){
        free_memory(); //frees memory when the programm is ending
        printf("Goodbye!\n");
        exit(0);
    }
    else{
        printf("Invalid command. Please try again\n");
        return 0;
    }
}

int word_is_valid(char *token){ //checks if word is valid based on the promt 
    int i = 0;
    while( token[i] != '\0'){
        if(isalpha(token[i]) == 0){
            return 0;
        }
        i++;
    }
    return 1;
}

int wordLenght(char *token){
    int words_letter_lenght = strlen(token);
    return words_letter_lenght;
}

int uniqLetters(char *token){
    int letters[26] = {0};
    int count = 0;
    int i = 0;
    while(token[i] != '\0'){
        if(isalpha(token[i]) != 0){
            char c = tolower(token[i]);
            if(letters[c - 'a'] != 1){
              letters[c - 'a'] = 1;
              count++;  
            }
        }
        i++;
    }
    return count;
}

void numOfTimes(wordList *found){
    if(found != NULL){
        found->numOfTimes++;
    }
}

wordList *find_word(char *token){ //searches if word is already saved at the list
    wordList *current = head;
    while(current != NULL){
        if(strcasecmp(current->word, token) == 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

wordList* create_new_node(char *token){
    wordList *new_node = malloc(sizeof(wordList));
    if(new_node == NULL){
        printf("Memory allocation failed, terminating programm );\n");
        exit(0);
    }
    new_node->word = strdup(token);
    if(new_node->word == NULL){
        printf("Memory allocation failed, terminating programm );\n");
        exit(0);
    }
    new_node->wordLenght = wordLenght(token);
    new_node->uniqLetters = uniqLetters(token);
    new_node->numOfTimes = 1;
    new_node->next = NULL;
    new_node->previous = NULL;
    new_node->insertionMode = 1;
    time_t present = time(NULL); 
    struct tm *t = localtime(&present);
    strftime(new_node->insertionDate, sizeof(new_node->insertionDate), "%d-%m-%Y", t); //calculates date 
    strftime(new_node->insertionTime, sizeof(new_node->insertionTime), "%H:%M:%S", t); //calculates time 
    return new_node;
}

void insert_alphabetically(wordList *new_node){
    if(head == NULL){
        head = new_node;
    }
    else{
        wordList *current = head;
        while(current != NULL && strcasecmp(current->word, new_node->word) < 0){
            current = current->next;
        }
        if(current == head){
            new_node->next = head;
            head->previous = new_node;
            head = new_node;
        }
        else if(current == NULL){ //insert at the end
            wordList *tail = head;
            while(tail->next != NULL){
                tail = tail->next;
            }
            tail->next = new_node;
            new_node->previous = tail;
        }
        else{ //insert before current
            new_node->next = current;
            new_node->previous = current->previous;
            if(current->previous != NULL){
                current->previous->next = new_node;
            }
            else{
                head = new_node;
            }
            current->previous = new_node;
        }
    } 
}

void print_word(char *token){
    int len = strlen(token);
    int count = len / 2; //changes half the letters 
    int *change = calloc(len, sizeof(int));
    change[0] = 0; //first letter is always capitalized
    int amongus = 0;
    while(amongus < count && len > 1){
        int x = 1 + (rand() % (len - 1)); //randomly chooses a letter to change
        if(!change[x] && token[x] != ' '){
            change[x] = 1;
            amongus++;
        }
    }
    int i = 0;
    for(i = 0; i < len; i++){
        if(change[i] && token[i] != ' '){
            printf(" _");
        }
        else{
            printf(" %c", token[i]);
        }
    }
    free(change);   
}

void free_memory(void){
    wordList *current = head;
    while(current != NULL){
        wordList *temp = current;
        current = current->next;
        free(temp->word);
        free(temp);
    }
    head = NULL;
}