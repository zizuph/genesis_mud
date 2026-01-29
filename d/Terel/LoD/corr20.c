/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corr20.c
 *
 * A corridor in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "corridor";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "monster/master_knight"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LOD_DIR + "guard_room2", "north", 0);
    add_exit(LOD_DIR + "corr21",   "south",  0);
    reset_room();
}

