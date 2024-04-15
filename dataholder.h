#ifndef __DATA_HOLDER_H__
#define __DATA_HOLDER_H__

#include <stdbool.h>
struct voter_str;
/** 
 *  Commonly reffered to as 'bucket entry', a dataholder structure contains:
 *    - a boolean referring to the emptyness of the bucket
 *    - the voter key
 *    - a pointer to the voter instance
 */
typedef struct dataholder_str{
    bool empty;
    unsigned int key;
    struct voter_str* voteraddr;

}dataholder;

/** @brief Initializes a dataholder with dummy values*/
void initialize_dataholder(dataholder* dh);

/**
 * @brief This dataholder instance now corresponds to this voter instance
 * @param  dataholder_ptr a pointer to the dataholder instance
 * @param  voter a pointer to the voter instance
 * @details The voter now belongs solely to the dataholder. The only other struture
 * that might be pointing at the voter instance is the inverted catalogue.
 */
void fill_dataholder( dataholder* dataholder_ptr, struct voter_str* voter);

/** @brief Destroy this dataholder instance along with its contained voter instance*/
void destroy_dataholder(dataholder* dh);




#endif