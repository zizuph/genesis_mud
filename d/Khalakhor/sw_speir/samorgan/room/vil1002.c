/**********************************************************************
 * - vil1002.c                                                      - *
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
	return ({10, 2});
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
            "the southwestern point of the village.\n");
  config_room("southern");
  add_item(({ "north", "northeast"}),
           "There is a building in that direction.\n");
  add_item(({"east", "northwest"}),
           "The street continues in that direction.\n");
  add_item(({"southwest", "southeast"}),
           "There is a rocky beach in that direction.\n");
  add_item("south", "Some sort of fishing pier is being built.\n");  
  add_item("west", "There is a tower in that direction.\n");
  add_item(({"tower", "guard tower"}),
           "A two-level guard tower has been constructed at the "+
           "southwestern point of the village.\n");
  
  add_exit("vil0901", "northwest");
  add_exit("vil1003", "east");
  add_exit("tower-sw", "west");
  
  add_fail(({"southwest", "southeast"}),
           "The rocks make it impossible to go in that direction.\n");
  add_fail("south", "The pier is still under construction.\n");  
  add_fail(({"northeast", "north"}),
           "A building blocks your passage.\n");

}
