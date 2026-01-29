/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest11.c
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
             SILVER_DIR + "monster/rodent"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(FOREST_EXIT,             "north", 0);
    add_exit(SILVER_DIR + "forest6",  "south", 0);
    add_exit(SILVER_DIR + "forest12", "east",  0);
    reset_room();
}
