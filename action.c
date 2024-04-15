#include "action.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash_table.h"
#include "voter.h"
#include <stdio.h>
#include <ctype.h>
#include <aio.h>
#include "postal_codes.h"

/**
 * @brief Checks if a string represents a number
 * @param str a string
 * @retval True if the string contains only numerical digits, otherwise return false
 */
bool isNumber(const char* str) {
    for(int c = 0; str[c] != '\0'; c++) {
        if(!isdigit(str[c])) return false;
    }
    return true;
}

void handle_action(hash_table* ht,postalCodes* pc, char input[][10] , int wordcount) {
    if (strcmp(input[0],"l") == 0) {
        if (wordcount != 2) {
            printf("ERROR INDICATIONS:\n\t- COMMAND: l needs a <pin>\n");
            return;
        }
        if (isNumber(input[1]) == false){
            printf("ERROR INDICATIONS:\n\t- Malformed Pin: <pin> is not an unsigned int\n");
            return;
        }
        voter* vt;
        if ( (vt = find_pin(ht, strtoul(input[1], NULL, 10))) != NULL) {
            print_voter(vt);
            return;
        }
        else {
            printf("ERROR INDICATIONS:\n\t- Participant %s not in cohort\n",input[1]);
            return;
        }
    }
    else if (strcmp(input[0],"i") == 0) {
        if ( wordcount != 5) {
            printf("ERROR INDICATIONS:\n\t- COMMAND: i needs a <pin> <lname> <fname> <zip>\n");
            return;
        }
        if (isNumber(input[1]) == false || isNumber(input[4]) == false ) {
            printf("ERROR INDICATIONS:\n\t- Malformed Pin/zip: <pin> or <zip> is not an unsigned int\n");
            return;
        }
        voter* vt;
        if ( (vt = find_pin(ht, strtoul(input[1], NULL, 10))) != NULL) {
            printf("ERROR INDICATIONS:\n\t- %s already exists\n",input[1]);
            return;
        }
        vt = create_voter(strtoul(input[1],NULL,10),input[2],input[3],strtoul(input[4],NULL,10));
        insert_record(ht,vt);
        printf("Inserted "); print_voter(vt);
        return;
    }
    else if (strcmp(input[0],"m") == 0) {
        if (wordcount != 2) {
            printf("ERROR INDICATIONS:\n\t- COMMAND: m needs a <pin>\n");
            return;
        }
        if (isNumber(input[1]) == false){
            printf("ERROR INDICATIONS:\n\t- Malformed Pin: <pin> is not an unsigned int\n");
            return;
        }
        voter* vt;
        if ( (vt = find_pin(ht, strtoul(input[1], NULL, 10))) == NULL) {
            printf("ERROR INDICATIONS:\n\t- %s does not exist\n",input[1]);
            return;
        }
        if ( vt->hasVoted == true ) printf("%u has already voted\n",vt->PID);        
        else {
            vt->hasVoted = true;
            printf("%u Marked Voted\n",vt->PID);
            insert_postalCodes(pc , vt);
        }
    }
    else if (strcmp(input[0],"bv") == 0) {
        if (wordcount != 2) {
            printf("ERROR INDICATIONS:\n\t- COMMAND: bv needs a <fileofkeys>\n");
            return;
        }
        FILE* fileofkeys = fopen(input[1],"r");
        if( fileofkeys == NULL ){
            printf("%s could not be opened\n",input[1]);
            return;
        }
        /*Time to parse the file*/
        size_t line_length = 0; /*for strtok()*/
        char* line = NULL;      /*for strtok()*/
        ssize_t char_nu;        /*for strtok()*/
        /*Set mvote command to be 'm'*/
        strcpy(input[0],"m");
        while ( (char_nu = getline(&line, &line_length, fileofkeys)) != -1 ) {
            char* ID_str = strtok(line,"\n");
            /*Set 'm' parametre*/
            strcpy(input[1],ID_str);
            handle_action(ht, pc, input, 2);
        }
        free(line);
        fclose(fileofkeys);

    }
    else if (strcmp(input[0],"v") == 0) {
        if (wordcount != 1) {
                    printf("ERROR INDICATIONS:\n\t- COMMAND: v needs no other parametres\n");
                    return;
        }
        unsigned int sum = find_total_voters(ht);
        printf("Voted so far %u\n",sum);
        return;
    }
    else if (strcmp(input[0],"perc") == 0) {
        if (wordcount != 1) {
                    printf("ERROR INDICATIONS:\n\t- COMMAND: perc needs no other parametres\n");
                    return;
        }
        float average = find_average_participants(ht);
        printf("%f\n",average);
    }
    else if ( strcmp(input[0],"print") == 0 && strcmp(input[1],"hashtable") == 0) {
        print_hash_table(ht);
        

    }
    else if ( strcmp(input[0],"z") == 0 ) {
        if (wordcount != 2) {
                    printf("ERROR INDICATIONS:\n\t- COMMAND: z needs a <zipcode>\n");
                    return;
                }
                if (isNumber(input[1]) == false){
                    printf("ERROR INDICATIONS:\n\t- Malformed : <zipcode> is not an unsigned int\n");
                    return;
                }
        print_PINs_inTK(pc, strtoul(input[1], NULL, 10));
    }
    else if ( strcmp(input[0],"o") == 0 ) {
        if (wordcount != 1) {
            printf("ERROR INDICATIONS:\n\t- COMMAND: o needs no other parametres\n");
            return;
        }
        print_Voters_num_inAllTK(pc);
    }
    else {
        printf("ERROR INDICATIONS:\n\t- Not a valid command\n");
        return;
    }

}

void check_user_arguments(int argc, char* argv[],\
                        int* registeredvoters_pos, int* bucketentries_pos)
{
    if (argc != 5){
        fprintf(stderr, "Wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }

    if      ( strcmp(argv[1],"-f") == 0 )    *registeredvoters_pos = 2;
    else if ( strcmp(argv[1], "-b") == 0)    *bucketentries_pos = 2;
    else {
        fprintf(stderr, "Missing flag for registered voters\n");
        exit(EXIT_FAILURE);
    }
    if      ( strcmp(argv[3],"-f") == 0 )    *registeredvoters_pos = 4;
    else if ( strcmp(argv[3], "-b") == 0)    *bucketentries_pos = 4;
    else {
        fprintf(stderr, "Missing flag for bucket entries\n");
        exit(EXIT_FAILURE);
    }
}

void parse_input(char* line, unsigned int* ID, char** fn,char** ln, unsigned int* tk){

    char* ID_str = strtok(line," ");
    *ID = strtoul(ID_str, NULL, 10);

    *fn = strtok(NULL," ");
    *ln = strtok(NULL," ");

    char* tk_str = strtok(NULL,"\n");
    *tk = strtoul(tk_str, NULL, 10);

    return;
}