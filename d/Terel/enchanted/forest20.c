/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest20.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit ENCHANT_DIR + "forest_room";

#include "enchanted.h"

/*
 * Function name: query_moving_object_list
 * Description:   return list of moving objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({ENCHANT_DIR + "monster/badger"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    add_exit(MAZE,                   "south",     0, HARD_TO_WALK);
    add_exit(MAZE,                   "west",      0, HARD_TO_WALK);
    add_exit(MAZE,                   "east",      0, HARD_TO_WALK);
    add_exit(MAZE,                   "north",     0, HARD_TO_WALK);
    add_exit(ENCHANT_DIR + "pines1", "southwest", 0);

    reset_room();
}
