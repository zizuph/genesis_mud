/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest4.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit ENCHANT_DIR + "forest_room";

#include "enchanted.h"

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({ENCHANT_DIR + "monster/sprite",
	     ENCHANT_DIR + "monster/sprite"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(MAZE,                    "south", 0, HARD_TO_WALK);
    add_exit(MAZE,                    "west",  0, HARD_TO_WALK);
    add_exit(MAZE,                    "east",  0, HARD_TO_WALK);
    add_exit(ENCHANT_DIR + "n_edge4", "north", 0, HARD_TO_WALK);
    reset_room();
}
