/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel5.c
 *
 * A tunnel in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "tunnel";

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/dog",
             LOD_DIR + "monster/bat2",
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
    add_exit(LOD_DIR + "tunnel6", "north", 0);
    add_exit(LOD_DIR + "tunnel4", "south", 0);
    reset_room();
}
