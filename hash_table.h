#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdbool.h>
/** @def MACRO_m @brief number m of buckets*/
#define MACRO_m 2

struct bucket_str;
struct voter_str;
/*Linear hashing data structure*/
typedef struct hash_table_str{
    float load; 
    float loadlimit;

    unsigned int keyCap_NonOverf_Buckets;   /*Key Capacity in Non Overflown Buckets*/
    unsigned int keys_nu;   /*Number of keys in the hash table.*/
    unsigned int bucketsize;        
    unsigned int pointer;
    unsigned int round;
/* The size which the hash table started with at the beginning of the round*/
    unsigned int bucket_prev_round;
/* An array of which each element contain a pointer to a list of buckets*/ 
    struct bucket_str** bucketarray;
    unsigned int bucketarray_size;
}hash_table;

/** @brief Initializes the hash table with MACRO_m size*/
void initialize_hash_tabe(hash_table* ht, float loadlimit, unsigned int bucketsize);

void destroy_hash_table(hash_table* ht);

/**
 * @brief Calculates the load λ of the hash table
 * @details Internally updates the hash table load
 * @retval λ
 */
float calculate_load(hash_table* ht);

/** @brief Insert a voter to the hash table */
void insert_record(hash_table*  ,struct voter_str*  );

/**
 * @brief Finds whether a voter already exists in the hash table.
 * @returns If pin is found, it returns a pointer to the corresponding voter,
 * otherwise it returns NULL.
 * @details It is used in 'l', 'm', 'i' mvote commands
 * */
struct voter_str* find_pin(hash_table* ht, unsigned int pin);

/** @returns Total number of registered voters who have already voted
 * @details It is used in 'v' mvote command
*/
unsigned int find_total_voters(hash_table* ht);

/**
 * @brief Prints all elements of the hash table
 * @details It is used in 'print hashtable' mvote command
 */
void print_hash_table(hash_table * ht);

/** @returns The average number of voters who have already voted
 * compared to the total amount of participants.
 * @details It is used in the 'perc' mvote command
 */
float find_average_participants(hash_table* ht);

#endif