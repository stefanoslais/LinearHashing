#ifndef __BUCKET_H__
#define __BUCKET_H__

struct dataholder_str;
struct voter_str;
/**
 * A bucket contains:
 * - its size
 * - an array of dataholder objects aka entries
 * - a pointer to the oveflow bucket
 * 
 */
typedef struct bucket_str{
    unsigned int bucketsize;
    struct dataholder_str* dataholder_array;
    struct bucket_str* ovf;

}bucket;

/**
 * @brief Creates a new bucket instance
 * @param bucketsize corresponds to the number of dataholder objects to be created
 * @returns a pointer to the new bucket
 */
bucket* create_empty_bucket(unsigned int bucketsize);

/**
 * @brief Insert voter to this bucket list
 * @param  voter pointer to voter instance
 * @param primary the beggining of the bucket list
 */
void insert_voter_tobucket(struct voter_str *voter, bucket* primary);

/**
 * @brief Empty the bucket and destroy this bucket instance
 * @param empty_this pointer to bucket to be destroyed
 * @warning It does not destroy the voters that are contained inside!
 * @details Function is called only during the bucket splitting procedure, after the rehashing
 * and repositioning of the voters.
 *  */
void empty_bucket(bucket* empty_this);

/**
 * @brief Destroy this bucket instance along with its contained voters
 * @param this_bucket pointer to the bucket to be destroyed
 */
void destroy_bucket(bucket** this_bucket);




#endif