#include "voter.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

voter* create_voter(unsigned int PID,char* lastName, char* firstName, unsigned int TK) {
    voter* new_voter = (voter*) malloc(sizeof(voter));
    if (new_voter == NULL) { 
        fprintf(stderr,"Not enough space for new voter\n");
        exit(EXIT_FAILURE);
    }
    new_voter -> PID = PID;
    new_voter -> lastName = strdup(lastName);
    new_voter -> firstName = strdup(firstName);
    new_voter -> TK = TK;
    new_voter -> hasVoted = false;
    
    return new_voter;
}

void destroy_voter(voter** voter_ptr) {
    voter* this_voter = *voter_ptr;

/*We free the dynamically allocated memebers of the struct*/
    free(this_voter -> lastName);
    this_voter -> lastName = NULL;
    free(this_voter -> firstName);
    this_voter -> firstName = NULL;
/*We free the struct itself and set the pointer to NULL
    (that's why we needed double pointer in the beginning)*/
    free(this_voter);
    (*voter_ptr) = NULL;
}

void print_voter(voter* vt) {
    printf("%u %s %s %u %c\n", vt->PID, vt->lastName, vt->firstName,vt->TK, (vt->hasVoted ? 'Y' : 'N'));
}