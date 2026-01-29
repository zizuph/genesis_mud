/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * n_edge7.c
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

    add_exit(ENCHANT_DIR + "n_edge8", "southwest", 0);
    add_exit(ENCHANT_DIR + "n_edge6", "northeast", 0);
    add_exit(ENCHANT_DIR + "forest7", "south", 0);
}

see_road()
{
    if (TP->query_skill(SS_LOC_SENSE) > 15) 
	return "The road continues to the northeast and south.\n";

    return "You find no road.\n";
}
