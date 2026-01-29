/**********************************************************************
 * - vil0301.c                                                      - *
 * - Village room.                                                  - *
 * - Created by Damaris@Genesis 02/2005                             - *
 * - added exit to the guard tower, Tapakah 04/2021                 - *
 **********************************************************************/
#pragma strict_types

#include "../defs.h"

inherit SAMORGAN_BASE;
/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
int *
query_local_coords()
{
	return ({2, 1});
}

int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}

void
create_khalakhor_room()
{
  set_xlong("A tower has been constructed at "+
            "the northwestern point of the village.\n");
	config_room("northern");
	add_item(({"southeast", "northeast"}),
           "There is a building in that direction.\n");
	add_item(({"south", "east"}),
           "The street continues in that direction.\n");
	add_item(({"west", "southwest"}),
           "There is a rocky beach in that direction.\n");
	add_item("north", "There is a forest in that direction.\n");
  add_item("northwest", "There is a tower in that direction.\n");
  add_item(({"tower", "guard tower"}),
           "A two-level guard tower has been constructed at the "+
           "northwestern point of the village.\n");

	add_exit("vil0202", "east");
	add_exit("vil0301", "south");
  add_exit("tower-nw", "northwest");

  add_fail(({"west", "southwest"}),
           "Rocks block your passage.\n");
	add_fail(({"northeast", "southeast"}),
           "A building stops your passage.\n");
	add_fail("north", "The trees are too thick making passage impossible.\n");
}
