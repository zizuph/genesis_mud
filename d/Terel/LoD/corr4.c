/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr4.c
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
    add_exit(LOD_DIR + "corr3",     "north", 0);
    add_exit(LOD_DIR + "corr5",     "south", 0);
    add_exit(LOD_DIR + "quart4e",   "east",  0);
    add_exit(LOD_DIR + "quart4w",   "west",  0);
}

