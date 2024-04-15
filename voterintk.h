#ifndef __VOTER_IN_TK_H__
#define __VOTER_IN_TK_H__

struct voter_str;

/**
 * A structure that contains:
 *  - a pointer to a voter that has already voted
 *  - a pointer to the next instance of the same structure in the list
 * 
 * It represents the white boxes in Schema 1 of Project Documentation
 * 
 */
typedef struct VoterinTK_str {
    struct voter_str* thisVoter;
    struct VoterinTK_str* next;
}VoterinTK;

struct voter_str;
/**
 * @brief Creates an instance of VoterinTK structure and initializes it with a voter instance
 * @param  this_voter a pointer to a voter instance
 * @returns a pointer to the created instance
 */
VoterinTK* create_VoterinTK(struct voter_str *this_voter);

/**
 * @brief Destroy a VoterinTK instance
 * @param vtk a double pointer to a VoterinTK instance
 * @warning It does not destroy the voter instance it points to!
 */
void destroy_VoterinTK(VoterinTK** vtk);

/**
 * @brief Print the PIN of the voter pointed by this VoterinTK instance
 * @param  this_VoterinTK pointer to a VoterinTK instance
 * @details It is used in 'o', 'z' mvote commands.
 */
void print_VoterinTK(VoterinTK* this_VoterinTK);






#endif