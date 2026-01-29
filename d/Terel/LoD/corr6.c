/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr5.c
 *
 * A corridor in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "corridor";

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/bat2"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LOD_DIR + "corr5",     "north", 0);
    add_exit(LOD_DIR + "hall",      "south", 0);
    add_exit(LOD_DIR + "quart6e",   "east",  0);
    add_exit(LOD_DIR + "quart6w",   "west",  0);
    reset_room();
}

