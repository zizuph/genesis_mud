/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest2.c
 *
 * A room in the silver forest.
 */

#include "/d/Terel/include/Terel.h"
inherit SILVER_DIR + "forest_room";

#include "local.h"

/*
 * Function name: query_moving_object_list
 * Description:   return list of moving objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({SILVER_DIR + "monster/rodent",
             SILVER_DIR + "monster/hare"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "South, you can see the town of Calathin.\n");
    
    add_exit(FOREST_EXIT,            "north", 0);
    add_exit(SILVER_DIR + "road1",   "south", 0);
    add_exit(SILVER_DIR + "forest1", "west",  0);
    add_exit(FOREST_EXIT,            "east",  0);
    reset_room();
}
