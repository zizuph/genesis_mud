/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * se_tower2.c
 *
 * Southeast tower on the second floor of the castle
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
    add_exit(WALL_HALL_DIR + "wh2_e1", "north", 0);
    add_exit(TOWER_DIR + "se_tower1",  "down",  0);
    add_exit(TOWER_DIR + "se_tower3",  "up",    0);
    reset_room();
}
