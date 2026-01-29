/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr15.c
 *
 * A corridor in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "corridor";

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/dog",
             LOD_DIR + "monster/dog"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LOD_DIR + "corr16",   "north", 0);              
    add_exit(LOD_DIR + "corr14",   "south", 0);       
    add_exit(LOD_DIR + "quart15e", "east",  0);
    add_exit(LOD_DIR + "quart15w", "west",  0);
    reset_room();
}

