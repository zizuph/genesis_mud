/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest15.c
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
    return ({SILVER_DIR + "monster/bird",
             SILVER_DIR + "monster/bird",
             SILVER_DIR + "monster/bird"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "You notice a small cave to the east.\n");

    add_exit(FOREST_EXIT,               "north", 0);
    add_exit(FOREST_EXIT,               "south", 0);
    add_exit("/d/Terel/mountains/redlair/cave01","east",0);

    add_exit(SILVER_DIR   + "forest14", "west",  0);
    reset_room();
}

go_east()
{
    object sorgum;

    sorgum = find_player("sorgum");
    if (sorgum && interactive(TP))
	sorgum->catch_msg(TP->query_real_name() + " entered the new orc " +
			  "caves.\n");

    return 0;
}
