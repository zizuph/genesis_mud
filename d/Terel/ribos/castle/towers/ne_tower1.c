/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ne_tower1.c
 *
 * Norhteast tower on the first floor of the castle
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit TOWER_DIR + "tower_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({RIBOS_DIR + "castle/monster/towerguard",
             RIBOS_DIR + "castle/monster/towerguard"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(WALL_HALL_DIR + "wh1_n8", "west",      0);
    add_exit(WALL_HALL_DIR + "wh1_e8", "south",     0);
    add_exit(TOWER_DIR + "ne_tower0",  "down",      0);
    add_exit(TOWER_DIR + "ne_tower2",  "up",        0);
    add_exit(CASTLE_DIR + "k_bath",    "southwest", 0);
    reset_room();
}
