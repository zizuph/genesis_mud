/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * n_edge6.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit ENCHANT_DIR + "n_edge_room";

#include <ss_types.h>
#include "enchanted.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_item("road", "@@see_road");

    add_exit(ENCHANT_DIR + "n_edge7",     "southwest", 0);
    add_exit(ENCHANT_DIR + "n_edge5",     "southeast", 0);
    add_exit(MAZE,                        "south",     0);
    add_exit(CALATHIN_DIR + "roads/road_s11","north",0);
}

see_road()
{
    if (TP->query_skill(SS_LOC_SENSE) > 15) 
	return "The road continues to the north and southwest.\n";

    return "You find no road.\n";
}
