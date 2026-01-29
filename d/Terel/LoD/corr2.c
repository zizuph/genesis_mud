/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr2.c
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
    add_exit(LOD_DIR + "corr1",     "north", 0);
    add_exit(LOD_DIR + "corr3",     "south", 0);
    add_exit(LOD_DIR + "quart2e",   "east",  0);        
    add_exit(LOD_DIR + "quart2w",   "west",  0);
}

