#include "voter.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include "hash_table.h"
#include "action.h"
#include <string.h>
#include "postal_codes.h"

/** @def loadlimit @brief load threshold*/
#define loadlimit 0.75
int main(int argc, char* argv[]) {

int registeredvoters_pos = -1;
int bucketentries_pos = -1;
check_user_arguments(argc,argv,&registeredvoters_pos,&bucketentries_pos);

FILE* registeredvoters_file = fopen(argv[registeredvoters_pos],"r");
if (!registeredvoters_file) {
    fprintf(stderr,"error in openin the registerd voters file\n");
    exit(EXIT_FAILURE);
}


hash_table hashTable;
initialize_hash_tabe(&hashTable,loadlimit, strtoul(argv[bucketentries_pos], NULL, 10)); //TSEKARO TO CASTING
postalCodes PostalCodes;
initialize_postalCodes(&PostalCodes);


size_t line_length = 0; /*will be used for strtok*/
char* line = NULL;      /*will be used for strtok*/
ssize_t char_nu;        /*will be used for strtok*/
while ( (char_nu = getline(&line, &line_length, registeredvoters_file)) != -1 ) {
    unsigned int ID;
    char* firstname;
    char* lastname;
    unsigned int TK;
    parse_input(line, &ID,&firstname,&lastname,&TK);
    voter* newvoter = create_voter(ID,lastname,firstname,TK);
    insert_record(&hashTable, newvoter);
}
free(line);


fclose(registeredvoters_file);


char input[50] = {'\0'};    //user input has maximum of 50 characters
char words[5][10];          //user input has maximum of 5 words 10 letters each

while(1) {
    printf("Command: ");
    /*Read user input from console*/
    if (fgets(input, 50, stdin) != NULL) {
        /*If user has typed exit as first word, then break out of loop*/
        char *token = strtok(input, " \n");
        if ( token != NULL && strcmp(token,"exit") == 0) {
            printf("exiting...\n");
            break;
        }
        /*Copy user input to words array*/
        int wordcount =0;
        while (token != NULL && wordcount < 5) {
            strcpy(words[wordcount], token);
            wordcount++;
            token = strtok(NULL, " \n");
        }
        /*Correspond appropriately to the commmand*/
        handle_action(&hashTable, &PostalCodes, words, wordcount);

    }
}
destroy_hash_table(&hashTable);
destroy_postalCodes(&PostalCodes);

    return 0;
}