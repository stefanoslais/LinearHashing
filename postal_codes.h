#ifndef __POSTAL_CODES_H__
#define __POSTAL_CODES_H__

struct TKnode_str;
/** @brief A struct that contains a list*/
typedef struct postalCodes_str {
    struct TKnode_str* head;
}postalCodes;

/**
 * @brief Initializes the head of the list
 * @param pC pointer to a postalCodes instance
 */
void initialize_postalCodes(postalCodes* pC);

/**
 * @brief Destroy the doubly linked list
 * @param pC pointer to a postalCodes instance
 */
void destroy_postalCodes(postalCodes* pC);

struct voter_str;
/**
 * @brief Insert a voter (that has voted) in the doubly linked list
 * @param PC pointer to a postalCodes instance
 * @param  this_voter pointer to a voter instance
 * @details It is used in the 'm' mvote command
 * @warning The check of whether this voter has voted again in the past
 * is being done in 'action.c'
 */
void insert_postalCodes(postalCodes* PC , struct voter_str* this_voter);

/** 
 * @brief Prints all PINs in a residential area code.
 * @param PC pointer to a postalCodes instance
 * @param TK residential area code
 * @details It prints 0 when the list is empty or 
 * the zipcode has not been found. 
 * It is used in the 'z' mvote command.
 */
void print_PINs_inTK(postalCodes* PC ,unsigned int TK);

/**
 * @brief Prints the zipcodes along with the number of voters who live in those residential areas
 * @param PC pointer to an instance of postalCodes
 * @details It is used in 'o' mvote command
 */
void print_Voters_num_inAllTK(postalCodes* PC);






#endif