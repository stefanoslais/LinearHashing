#include "postal_codes_node.h"
#include <stdlib.h>
#include <stdio.h>
#include "voterintk.h"


TKnode* create_TKnode(unsigned int TK) {
//Create TKnode
    TKnode* tkn = malloc(sizeof(TKnode));
    if (tkn == NULL) {
        fprintf(stderr,"Not enought memory for TKnode\n");
        exit(EXIT_FAILURE);
    }
//Initialize it
    tkn->head = NULL;
    tkn->tail = NULL;
    /* Will soon change after the insertion of the node in the doubly linked list*/
    tkn->next = NULL;
    tkn->previous = NULL;

    tkn->voters_num = 0;
    tkn->TK = TK;

    return tkn;
}
void destroy_TKnode(TKnode** tkn) {
    TKnode* this_TKnode = *tkn;
    VoterinTK* this_VoterinTK = this_TKnode->head;
    while (this_VoterinTK != NULL) {
        VoterinTK* next = this_VoterinTK->next;
        destroy_VoterinTK(&this_VoterinTK);
        this_VoterinTK = next;
    }
    free(*tkn);
    *tkn = NULL;
    return;
}

void insert_TKnode(TKnode** pChead, TKnode* here, TKnode* this_node) {
    /*If the doubly linked list is empty*/
    if (*pChead == NULL )   *pChead = this_node;
    /*otherwise, insert in the end of the list pointed by 'here' pointer*/
    else {
        here->next = this_node;
        this_node->previous = here;
    }
    return;
}

void insert_Voterin_TKnode(TKnode* this_TKnode , struct voter_str* this_voter) {
    VoterinTK* vtk = create_VoterinTK(this_voter);
    /*If the list is empty, set head and tail*/
    if ( this_TKnode->voters_num == 0 ) {
        this_TKnode->head = vtk;
        this_TKnode->tail = vtk;
    }
    /*otherwise, insert vtk after the tail and update the tail*/
    else {
        this_TKnode->tail->next = vtk;
        this_TKnode->tail = vtk;
    }
    /*update the number of voters*/
    this_TKnode->voters_num++;
}

void print_TKnode(TKnode* this_TKnode) {
    
    /*Start from the head*/
    VoterinTK* this_VoterinTK = this_TKnode->head;
    /*As long tail hasn't been reached*/
    while ( this_VoterinTK != (this_TKnode->tail)) {
        print_VoterinTK(this_VoterinTK);
        this_VoterinTK = this_VoterinTK->next;
    }
    /*Print tail*/
    print_VoterinTK(this_VoterinTK);


}


void switch_TKnodes( TKnode** PChead, TKnode* this_TKnode) {

    /*Get previous node*/
    TKnode* previous = this_TKnode->previous;
    /*As long there exists a previous node AND the doubly linked list is not in descending order*/
    while (previous != NULL  && previous->voters_num < this_TKnode->voters_num ) {
        /*Switch the nodes by moving this_TKnode to the left*/
        /*First, update the next pointers*/
        previous->next = this_TKnode->next;
        this_TKnode->next = previous;

        /*Then, update the previous pointers*/
        this_TKnode->previous = previous->previous;
        previous->previous = this_TKnode;

        /*Lastly, we need to update what is left and right of the switched nodes,
        in case they exist*/
        if ((this_TKnode->previous) != NULL)    this_TKnode->previous->next = this_TKnode;
        if ((previous->next) != NULL)           previous->next->previous = previous;

        /*Update the previous pointer for the interation to continue properly*/
        previous = this_TKnode->previous;
    }
    /*If the continuous switching reached the beggining of the doubly linked list,
    update its head*/
    if (previous == NULL)  *PChead = this_TKnode;
    
    return;
}
