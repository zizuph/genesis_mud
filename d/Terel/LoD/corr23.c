/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr23.c
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
    add_exit(LOD_DIR + "corr22",   "north", 0);              
    add_exit(LOD_DIR + "corr24",   "south", 0);       
    add_exit(LOD_DIR + "quart23e", "east",  0);
    add_exit(LOD_DIR + "quart23w", "west",  0);
}

