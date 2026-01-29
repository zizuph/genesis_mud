/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnelr5.c
 *
 * A tunnel in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "tunnelr";

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/bat2",
             LOD_DIR + "monster/bat2",
             LOD_DIR + "monster/bat2"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LOD_DIR + "corr12",   "north", 0);       
    add_exit(LOD_DIR + "tunnelr5a", "west", 0);
    add_exit(LOD_DIR + "tunnelr4b", "east", 0);
    reset_room();
}
