/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr13.c
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
    add_exit(LOD_DIR + "corr14",   "north", 0);              
    add_exit(LOD_DIR + "corr12",   "south", 0);       
    add_exit(LOD_DIR + "quart13e", "east",  0);
    add_exit(LOD_DIR + "quart13w", "west",  0);
}

