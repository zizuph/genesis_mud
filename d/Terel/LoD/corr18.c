/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr18.c
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
    add_exit(LOD_DIR + "tunnel1",  "north",  0);
    add_exit(LOD_DIR + "quart18s", "south",  0);       
    add_exit(LOD_DIR + "corr19",   "east",   0);
    add_exit(LOD_DIR + "corr17",   "west",   0);       
    reset_room();
}

