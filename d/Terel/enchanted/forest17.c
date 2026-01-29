/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest17.c
 *
 * Modified by Lilith: connected sacred garden in Calathin toascii
 *    this location, which is north of the Minstrels. The SG used
 *    to be the minstrel location.
 */

#include "/d/Terel/include/Terel.h"
inherit ENCHANT_DIR + "forest_room";

#include <ss_types.h>
#include "enchanted.h"

#define SG_CONN "/d/Terel/common/town/garden/copse3"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_item("road", "@@see_road");
   
    add_exit(ENCHANT_DIR + "road_s12", "south",     0, HARD_TO_WALK);
    add_exit(SG_CONN,                  "west",      0, HARD_TO_WALK);
    add_exit(MAZE,                     "east",      0, HARD_TO_WALK);
    add_exit(ENCHANT_DIR + "forest7",  "north",     0, HARD_TO_WALK);
    add_exit(ENCHANT_DIR + "oaks1",    "northwest", 0);
}

see_road()
{
    if (TP->query_skill(SS_LOC_SENSE) > 25) 
	return "The road continues to the north and south.\n";

    return "You find no road.\n";

}
