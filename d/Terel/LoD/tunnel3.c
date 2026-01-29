/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel3.c
 *
 * A tunnel in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "tunnel";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "monster/iron_guard"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LOD_DIR + "tunnel4", "north", 0);
    add_exit(LOD_DIR + "tunnel2", "south", 0);
    reset_room();
}
