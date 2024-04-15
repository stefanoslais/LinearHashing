#include "bucket.h"
#include "dataholder.h"
#include "voter.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

void insert_voter_tobucket(voter* voter, bucket* primary) {

/*Check  primary bucket*/
    unsigned int d =0;
    for ( d = 0; d < primary->bucketsize; d++) {
        if ( primary->dataholder_array[d].empty == true ) break;
    }
/*If an empty data holder was found in the primary bucket, insert it there*/
    if ( d < primary->bucketsize ) {
        fill_dataholder(&(primary->dataholder_array[d]) , voter);
        return;
    }
/*If not, search for an empty data holder in the overflow buckets in case they exist*/
    bucket* this_ovf = primary->ovf;
    while ( this_ovf != NULL ) {
/*Same as before (repetion of code, but clarity to the eye)*/
        for ( d = 0; d < this_ovf->bucketsize; d++) {
            if ( this_ovf->dataholder_array[d].empty == true ) break;
        }
        if ( d < this_ovf->bucketsize ) {
            fill_dataholder(&(this_ovf->dataholder_array[d]) , voter);
            return;
        }
/*If it didn't find an empty dataholder in this overflow bucket, move on to the next ovf*/
        this_ovf = this_ovf->ovf;
    }
/*In this part of the program, we have
  neither found a free spot in primary nor in the ovf buckets*/
/*Time to create a new overflow bucket */
    bucket* new_ovf_bucket = create_empty_bucket(primary->bucketsize);
    fill_dataholder(&(new_ovf_bucket->dataholder_array[0]) , voter);
/*Find the end of the bucket list and insert it there*/
    bucket* last_bucket = primary;
    while( (last_bucket->ovf) != NULL ) last_bucket = last_bucket->ovf;
    last_bucket->ovf = new_ovf_bucket;
    return;
}



bucket* create_empty_bucket(unsigned int bucketsize)  {
    bucket* bucket_ptr = (bucket*)malloc(sizeof(bucket));
    if (bucket_ptr == NULL) {
        fprintf(stderr,"Not enough memory for bucket\n");
        exit(EXIT_FAILURE);
    }
    bucket_ptr->ovf = NULL;
    bucket_ptr->bucketsize = bucketsize;
    /*Create 'bucketsize' number of data holders and initialize them*/
    bucket_ptr->dataholder_array = (dataholder*) malloc(bucketsize * sizeof(dataholder)); 
    if (bucket_ptr->dataholder_array == NULL) {
        fprintf(stderr,"Not enough memory for dataholder array\n");
        exit(EXIT_FAILURE);
    }
    for (unsigned int d = 0; d < bucketsize; d++) {
        initialize_dataholder(&(bucket_ptr->dataholder_array[d]));
    }
    return bucket_ptr;
}


void empty_bucket(bucket* empty_this) {
    empty_this->ovf = NULL;

    for ( unsigned int d = 0 ; d < empty_this->bucketsize; d++) 
        empty_this->dataholder_array[d].voteraddr = NULL;
        
    free(empty_this->dataholder_array);
    free(empty_this);
}

void destroy_bucket(bucket** this_bucket) {
    bucket* destroy_this = *this_bucket;
    /*For every dataholder that is not empty, destroy it, along with the voters*/
    for ( unsigned int d = 0; \
                d < destroy_this->bucketsize \
                && destroy_this->dataholder_array[d].empty == false; \
                d++ ) {
        destroy_dataholder(&(destroy_this->dataholder_array[d]));
        
    }
    free(destroy_this->dataholder_array);
    free(destroy_this);
    *this_bucket = NULL;
    return;
}

