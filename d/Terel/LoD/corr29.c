/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr29.c
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
    add_exit(LOD_DIR + "corr28",   "north", 0);              
    add_exit(LOD_DIR + "quart29e", "east",  0);
    add_exit(LOD_DIR + "quart29w", "west",  0);
    add_exit(LOD_DIR + "quart29s","south", 0);
}

