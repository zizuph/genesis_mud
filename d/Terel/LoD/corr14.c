/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr14.c
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
    add_exit(LOD_DIR + "corr15",   "north", 0);              
    add_exit(LOD_DIR + "corr13",   "south", 0);       
    add_exit(LOD_DIR + "quart14e", "east",  0);
    add_exit(LOD_DIR + "quart14w", "west",  0);
}

