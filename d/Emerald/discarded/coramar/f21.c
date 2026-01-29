/*
 * F21.c
 * Forest of Coramar
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    
    set_long("   The narrow path is formed almost accidentally here. Huge tangles of "+
	"trees, branches, vines and enormous bushes all seem to be thrown together "+
	"in two giant piles. The small, narrow space between the two piles of foliage "+
	"forms a small path. To the southwest, that path becomes buried by more overgrowth "+
	"and eventual darkness. To the east, the path comes to a fork and gradually "+
	"becomes wider and more easily navigated.\n\n");


    add_fexit(CORAMAR+"f22", "east", 0);
    add_fexit(CORAMAR+"f20", "southwest", 0);
}