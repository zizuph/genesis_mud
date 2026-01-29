/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest25.c
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
    return ({SILVER_DIR + "monster/rabbit",
             SILVER_DIR + "monster/rabbit",
             SILVER_DIR + "monster/rabbit"});    
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "East, between the trees, you see a " +
	     "ramshackle hut.\n");

    add_item(({"hut", "ramshackle hut"}), "It's a very old wooden hut.\n");

    add_exit(FOREST_EXIT,                "south", 0);
    add_exit(FOREST_EXIT,                "west",  0);
    add_exit(SILVER_DIR + "eremite_hut", "east",  0);
    reset_room();
}

