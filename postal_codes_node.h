#ifndef __POSTAL_CODES_NODE_H__
#define __POSTAL_CODES_NODE_H__

struct VoterinTK_str;
/**
 * A structure that contains a list of voters that have already voted,
 * and who also live in the same residential area.
 * This structure is part of a doubly linked list.
 * The structure contains the following data:
 *  - The number of the voters in contains
 *  - The residential area code it represents
 *  - A 'head' pointer pointing at the beggining of its containing list
 *  - A 'tail' pointer pointing at the end of its containing list
 *  - A 'next' pointer pointing at the next instance of the same structure
 *  - A 'previous' pointer pointing at the previous instance of the same structure
 * 
 * It represents the blue boxes shown in Figure 1 of Project Documentation
 */
typedef struct TKnode_str {
    unsigned int voters_num;
    struct VoterinTK_str* head;
    struct VoterinTK_str* tail;
    struct TKnode_str* next;
    struct TKnode_str* previous;
    unsigned int TK;


}TKnode;

/**
 * @brief Creates a TKnode instace and initialises it
 * @param TK residential area code
 * @returns a pointer to the new instance
 */
TKnode* create_TKnode(unsigned int TK);
/**
 * @brief Destroy the node along with its containing list
 * @param tkn a double pointer to a TKnode instance
 */
void destroy_TKnode(TKnode** tkn);

/**
 * @brief Insert a newly created TKnode instance at the end of the doubly linked list
 * @param pChead a double pointer to the head of the doubly linked list
 * @param here a pointer to the last TKnode of the doubly linked list, before the insertion
 * @param this_node pointer to a newly created TKnode
 */
void insert_TKnode(TKnode** pChead,TKnode* here, TKnode* this_node);

struct voter_str;
/**
 * @brief Create a VoterinTK instance and insert it in the list
 * @param this_TKnode pointer to a TKnode instance
 * @param this_voter  pointer to a voter instance
 */
void insert_Voterin_TKnode(TKnode* this_TKnode , struct voter_str* this_voter);

/**
 * @brief Prints out the containing list of voters
 * @param this_TKnode pointer to a TKnode instance
 * @details It is used in the 'z' mvote command
 */
void print_TKnode(TKnode* this_TKnode);

/**
 * @brief Move this node to its proper place in the doubly linked list
 * @param [out] PChead a double pointer to the head of the doubly linked list
 * @param this_TKnode pointer to the node to be moved
 */
void switch_TKnodes( TKnode** PChead, TKnode* this_TKnode);
#endif