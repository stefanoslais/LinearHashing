#include "postal_codes.h"
#include "voter.h"
#include "postal_codes_node.h"
#include <stdlib.h>
#include <stdio.h>

void initialize_postalCodes(postalCodes* pC) {
    pC->head = NULL;
}

void destroy_postalCodes(postalCodes* pC) {
    /*Starting from the head*/
    TKnode* this_TKnode = pC->head;
    /*till end is reached*/
    while (this_TKnode != NULL) {
        TKnode* next = this_TKnode->next;
        /*destroy the TKnode*/
        destroy_TKnode(&this_TKnode);
        this_TKnode = next;
    }
    return;
}


void insert_postalCodes(postalCodes* PC , voter* this_voter) {
    unsigned int TK = this_voter->TK;
//If the list is empty, insert voter at the begin of the list
    if ( PC->head == NULL ) {
        TKnode* tk_node = create_TKnode(TK);
        insert_TKnode(&(PC->head), NULL, tk_node);
        insert_Voterin_TKnode(tk_node,this_voter);
        return;
    }
//If the TK node already exists, check whether there's need to be a switch
    TKnode* after = PC->head;
    TKnode* before = NULL;
    while( after != NULL ) {
        //If the TK node already exists
        if ( after->TK == TK ) {
            insert_Voterin_TKnode(after , this_voter);
            /*Now the number of voters in the 'after' TKnode has incremented*/
            /*Compare the number of voters in the 'after' TKnode with the previous node, pointed
            to by 'before' pointer*/
            if ( before != NULL && after->voters_num > before->voters_num) {
                switch_TKnodes( &(PC->head), after);
            }
            return;
        }
        /*Update 'after' and 'before' pointers*/
        before = after;
        after = after->next;
    }
//The TK node does not already exist, insert it at the end
    TKnode* tk_node = create_TKnode(TK);
    insert_TKnode(&(PC->head), before, tk_node);
    insert_Voterin_TKnode(tk_node,this_voter);
}


void print_PINs_inTK(postalCodes* PC, unsigned int TK) {
    bool zipcode_found = false;
    /*If list is empty*/
    if( PC->head == NULL )  {
        printf("0 voted in %u\n",TK);
        return;
    }
    /*Start from the head*/
    TKnode* this_node = PC->head;
    while( this_node != NULL ) {
        /*If the zipcode is found, break out of the loop*/
        if ( this_node->TK == TK ) { zipcode_found = true; break; }
        else    this_node = this_node->next;
    }
    if ( zipcode_found == false ) {
        printf("0 voted in %u\n",TK);
        return;
    }
    printf("%u voted in %u\n", this_node->voters_num, this_node->TK);
    /*Print PINs of the voters who live in that zipcode*/
    print_TKnode(this_node);
}


void print_Voters_num_inAllTK(postalCodes* PC) {
    /*If list is empty*/
    if ( PC->head == NULL ) return;
    /*otherwise start from head*/
    else {
        TKnode* this_TKnode = PC->head;
        /*till end is reached*/
        while( this_TKnode != NULL ) {
            printf("%u %u\n", this_TKnode->TK, this_TKnode->voters_num );
            this_TKnode = this_TKnode->next;
        }
    }

}
