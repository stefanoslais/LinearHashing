#ifndef __ACTION_H__
#define __ACTION_H__

struct hash_table_str;
struct postalCodes_str;

/**
 * @brief Takes action depending on the user input command
 * @param [out] ht pointer to the hashtable
 * @param [out] pc pointer to the inverted catalogue
 * @param input the user input array
 * @param wordcount number of user input words
 */
void handle_action(struct hash_table_str* ht, struct postalCodes_str* pc, char input[][10] , int wordcount);

/*Checks correctness of number of arguments and locates which arguments are reffered to the number of entries and which are reffered to the file of voters
@param [out] registeredvoters_pos Position of <registeredvoters> in argv array
@param [out] bucketentries_pos Position of<bucketentries> in argv array*/
void check_user_arguments(int argc, char* argv[], int* registeredvoters_pos, int* bucketentries_pos);

/**
 * @brief Parse file of registered voters
 * 
 * @param line buffer containing a line from the file
 * @param [out] ID  the PIN of the voter
 * @param [out] fn  first name of the voter
 * @param [out] ln  last name of the voter
 * @param [out] tk  the zipcode where the voter lives
 * 
 */
void parse_input(char* line, unsigned int* ID, char** fn,char** ln, unsigned int* tk);





#endif