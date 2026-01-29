/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest7.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit ENCHANT_DIR + "forest_room";

#include <ss_types.h>
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
    add_item("road", "@@see_road");
   
    add_exit(ENCHANT_DIR + "forest17", "south", 0, HARD_TO_WALK);
    add_exit(MAZE,                     "west",  0, HARD_TO_WALK);
    add_exit(MAZE,                     "east",  0, HARD_TO_WALK);
    add_exit(ENCHANT_DIR + "n_edge7",  "north", 0, HARD_TO_WALK);
    reset_room();
}

/*
 * Function name: see_road
 * Description:   If the player has high enough location sense, they may
 *                see the road.
 */
public string
see_road()
{
    if(TP->query_skill(SS_LOC_SENSE) > 25)
	return "The road continues to the north and south.\n";
    
    if(TP->query_skill(SS_LOC_SENSE) > 15)
	return "The road continues to the north.\n";
    
    return "You find no road.\n";
}
