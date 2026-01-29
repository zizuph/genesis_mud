/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel9.c
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
    return ({LOD_DIR + "monster/evil_guard"});
}

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
    add_exit(LOD_DIR + "tunnel10", "north",  0);
    add_exit(LOD_DIR + "tunnelr6", "south",  0);
    reset_room();
}
