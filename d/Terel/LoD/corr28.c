/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr28.c
 *
 * A corridor in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "corridor";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LOD_DIR + "corr27",   "north", 0);              
    add_exit(LOD_DIR + "corr29",   "south", 0);       
    add_exit(LOD_DIR + "quart28e", "east",  0);
    add_exit(LOD_DIR + "quart28w", "west",  0);
}

