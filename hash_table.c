#include "hash_table.h"
#include "bucket.h"
#include "voter.h"
#include "dataholder.h"
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
/**
 * @brief h_i(k) = k mod 2^i * m
 * @param k key
 * @param i round
 * @param m initial number of buckets, set by MACRO_m
 * @retval the position in the hash table in which to insert the key 
 */
unsigned int hashfunction(unsigned int k, unsigned int i , unsigned int m) {
    return k % ((unsigned int)pow(2,i) * m);
}


void initialize_hash_tabe(hash_table* ht, float loadlimit, unsigned int bucketsize) {


    ht->load = 0.0; /* dummy value, will certainly change after the insertion of the first element*/
    ht->loadlimit= loadlimit;
    
    ht->pointer = 0;
    ht->round = 0;
    ht->bucketsize = bucketsize;


/* We create a MACRO_m size hash table*/
    ht->bucketarray = (bucket**) malloc(MACRO_m * sizeof(bucket*));
    if (ht->bucketarray == NULL) {
        fprintf(stderr,"Not enough memory for bucketarray\n");
        exit(EXIT_FAILURE);
    }
/* We insert the newly created buckets to the array */
    for ( unsigned int b=0; b < MACRO_m ; b++) {
        bucket* newbucket_ptr = create_empty_bucket(ht->bucketsize);
        ht->bucketarray[b] = newbucket_ptr;
    }
    ht->bucketarray_size = MACRO_m;
    ht->bucket_prev_round = MACRO_m;

    ht->keyCap_NonOverf_Buckets = MACRO_m * bucketsize;
    ht->keys_nu = 0;
}


void destroy_hash_table(hash_table* ht) {
    /*For every member of the array, aka for every bucket list*/
    for (unsigned int d=0; d < ht->bucketarray_size; d++) {
        bucket* this_bucket = ht->bucketarray[d];
        /*Iterate over all buckets (primary and overflows) and destroy them*/
        while (this_bucket != NULL) {
            bucket* next = this_bucket->ovf;
            destroy_bucket(&this_bucket);
            this_bucket = next;
        }
    }
    free(ht->bucketarray);
}

void bucket_splitting(struct hash_table_str*);

void insert_record(hash_table* ht ,voter* voter_ptr) {
    unsigned int key = voter_ptr->PID;
    unsigned int bucket_pos = hashfunction(key, ht->round, MACRO_m);
    
    if ( bucket_pos < ht->pointer ) {
        bucket_pos = hashfunction(key, ht->round + 1, MACRO_m);
    }
    insert_voter_tobucket(voter_ptr, ht->bucketarray[bucket_pos]);
    ht->keys_nu++;

    if (calculate_load(ht) > ht->loadlimit ) {
        /*Increment hash table*/
        bucket_splitting(ht);
        ht->pointer++;
        if ( ht->bucketarray_size == 2 * ht->bucket_prev_round) {
            ht->round++;
            ht->pointer = 0;
            ht->bucket_prev_round = ht->bucketarray_size;
        }

    }
}


float calculate_load(hash_table* ht) { 
    ht->load = (float)ht->keys_nu / ht->keyCap_NonOverf_Buckets;
    return ht->load;
}

/**
 * @brief For all the buckets pointed to by pointer, we rehash their contained keys
 * and reposition them in the hash table.
 */
void bucket_splitting(hash_table* ht) {
    /*Firstly, we expand are bucket array*/ 
    bucket** expanded_bucketarray ;
    expanded_bucketarray = (bucket**) realloc(ht->bucketarray,(ht->bucketarray_size + 1) * sizeof(bucket*));
    if (expanded_bucketarray == NULL ) {
        fprintf(stderr,"Not enough memory for bucket array of size %u", ht->bucketarray_size);
        exit(EXIT_FAILURE);
    }
    ht->bucketarray = expanded_bucketarray;
    /*We populate the new element of the array, aka the new pointer to a list of buckets*/
    bucket* newbucket_ptr = create_empty_bucket(ht->bucketsize);
    ht->bucketarray[ht->bucketarray_size] = newbucket_ptr;

    /*Update the following sizes*/
    ht->bucketarray_size++;
    ht->keyCap_NonOverf_Buckets+=ht->bucketsize;

    /*Then, we detach the list of buckets pointed to by the pointer as following:*/

    /*We store the beggining of the bucket list that the pointer points to*/
    bucket* splitted_list_begin =  ht->bucketarray[ht->pointer];
    /*We detach the list from the hash table*/
    ht->bucketarray[ht->pointer] = NULL;
    /*The pointer bucket list cannot be left empty, so we populate it.*/
    ht->bucketarray[ht->pointer] = create_empty_bucket(ht->bucketsize);

    /*For all keys of the splitted list we rehash and reposition our data as following:*/
    bucket* this_bucket = splitted_list_begin;
    /*For  all buckets in the splitted list*/
    while( this_bucket != NULL ){
        /*We check their data holders. If they are not empty, 
        they contain a key that needs to be rehashed*/
        for ( unsigned int d = 0; \
            /*If one of the following two conditions fail, 'for' loop will break out*/    
             d < this_bucket->bucketsize \
             && this_bucket->dataholder_array[d].empty == false; \
             d++ ) {
            unsigned int key = this_bucket->dataholder_array[d].key;
            unsigned int new_bucketpos = hashfunction(key, ht->round + 1, MACRO_m);
            insert_voter_tobucket(this_bucket->dataholder_array[d].voteraddr, ht->bucketarray[new_bucketpos]);
        }

        bucket* empty_this = this_bucket;
        this_bucket = this_bucket->ovf;
        empty_bucket(empty_this);
    }
}



void print_hash_table(hash_table * ht) {
    /*For every element of the array, aka for bucket list the array points to*/
    for( unsigned int b = 0; b < ht->bucketarray_size; b++) {
        bucket * thisb = ht->bucketarray[b];
        printf("Bucket %u:\n",b);
        while (thisb != NULL) {
            /*For every dataholder, as long as it is not empty*/
            for ( unsigned int d=0; d < thisb->bucketsize \
                && thisb->dataholder_array[d].empty == false ;\
                d++) {
                printf("\tdataholder[%u]\n",d);
                print_voter(thisb->dataholder_array[d].voteraddr);
            }
            printf("\t---\n");
            thisb = thisb->ovf;
        } 

    }
}


voter* find_pin(hash_table* ht, unsigned int pin) {
    unsigned int key = pin;
    unsigned int bucket_pos = hashfunction(key, ht->round, MACRO_m);
    
    if ( bucket_pos < ht->pointer ) {
        bucket_pos = hashfunction(key, ht->round + 1, MACRO_m);
    }
/*Traverse the bucket list to find the pin.*/
    bucket* thisb= ht->bucketarray[bucket_pos];
    while (thisb != NULL) {
        for ( unsigned int d=0; d < thisb->bucketsize /*for every dataholder element*/ \
            && thisb->dataholder_array[d].empty == false; /*as long as it contains information*/\
            d++) {
            if ( key == thisb->dataholder_array[d].key )
                return thisb->dataholder_array[d].voteraddr;
        }
        thisb = thisb->ovf;
    } 
/*If pin was not found, return NULL*/
    return NULL;
}


unsigned int find_total_voters(hash_table* ht) {
    unsigned int sum =0;
    /*For every element of the array, aka for bucket list the array points to*/
    for (unsigned int position=0; position < ht->bucketarray_size; position++) {
        bucket* thisb = ht->bucketarray[position];
        /*For every bucket*/
        while (thisb != NULL) {
            /*For every dataholder, as long as it is not empty*/
            for ( unsigned int d=0; d < thisb->bucketsize \
                && thisb->dataholder_array[d].empty == false ;\
                d++) {
                voter* thisv = thisb->dataholder_array[d].voteraddr;
                /*If the registered voters has voted, include them in the sum*/
                if ( thisv->hasVoted == true )  sum++;
            }
            thisb = thisb->ovf;
        } 
    }
    return sum;
}


float find_average_participants(hash_table* ht) {
    unsigned int voted_voters = find_total_voters(ht);
    unsigned int total_voters = 0;
    /*For every element of the array, aka for bucket list the array points to*/
    for (unsigned int position=0; position < ht->bucketarray_size; position++) {
        bucket* thisb = ht->bucketarray[position];
        /*For every bucket*/
        while (thisb != NULL) {
            /*For every dataholder, as long as it is not empty*/
            for ( unsigned int d=0; d < thisb->bucketsize \
                && thisb->dataholder_array[d].empty == false ;\
                d++) {
            /*Count the participant, regardless of whether they have voted or not*/
                total_voters++;
            }
            thisb = thisb->ovf;
        } 
    }
    if ( total_voters == 0 ) return 0.0f;
    else return (float)voted_voters / total_voters;



}
