#include "dataholder.h"
#include "voter.h"
#include <stddef.h>

void initialize_dataholder(dataholder* dh) {
    dh->empty = true;
    dh->key = 0; //dummy value
    dh->voteraddr = NULL;
}

void fill_dataholder( dataholder* dataholder_ptr , voter *voter) {
    dataholder_ptr->empty = false;
    dataholder_ptr->key = voter->PID;
    dataholder_ptr->voteraddr = voter;
}

void destroy_dataholder(dataholder* dh) {
    destroy_voter(&(dh->voteraddr));
    return;
}


