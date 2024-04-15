#include "voterintk.h"
#include <stdlib.h>
#include <stdio.h>
#include "voter.h"
#include <stdio.h>

VoterinTK* create_VoterinTK (struct voter_str* this_voter) {
//Create the node
    VoterinTK* vtk = malloc(sizeof(VoterinTK));
    if (vtk == NULL) {
        fprintf(stderr, "Not enought memory for VoterinTK node\n");
        exit(EXIT_FAILURE);
    }
//Initialize it
    vtk->thisVoter = this_voter;
    vtk->next = NULL;

    return vtk;
}

void destroy_VoterinTK(VoterinTK** vtk) {
    (*vtk)->thisVoter = NULL;
    (*vtk)->next = NULL;
    free(*vtk);
    *vtk = NULL;
    return;
}

void print_VoterinTK(VoterinTK* this_VoterinTK) {
    printf("%u\n", this_VoterinTK->thisVoter->PID);
}
