/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr5.c
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
    add_exit(LOD_DIR + "corr4",     "north", 0);
    add_exit(LOD_DIR + "corr6",     "south", 0);
    add_exit(LOD_DIR + "quart5e",   "east",  0);
    add_exit(LOD_DIR + "quart5w",   "west",  0);
}

