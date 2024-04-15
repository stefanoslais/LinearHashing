#ifndef __VOTER_H__
#define __VOTER_H__


#include <stdbool.h>

typedef struct voter_str{
    unsigned int PID;
    char* lastName;
    char* firstName;
    unsigned int TK;
    bool hasVoted;
}voter;

/**
 * @brief Creates a voter instance
 * @param lastName is allocated dynamically
 * @param fistName is allocated dynamically
 * @returns a pointer to the voter instance
 */
voter* create_voter(unsigned int PID,char* lastName, char* firstName, unsigned int TK);
void destroy_voter(voter **);

void print_voter(voter* );

#endif