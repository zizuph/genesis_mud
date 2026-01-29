/**********************************************************************
 * - vil0209.c                                                      - *
 * - Village room.                                                  - *
 * - Created by Damaris@Genesis 02/2005                             - *
 * - Slightly modified for future developments by Tapakah, 04/2021  - *
 * - added exit to the guard tower, Tapakah 04/2021                 - *
 **********************************************************************/
#pragma strict_types

#include "../defs.h"

inherit SAMORGAN_BASE;
inherit UTILS;

/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/

int *
query_local_coords()
{
  return ({2, 9});
}

int *
query_global_coords()
{
  return SAMORGAN_COORDS;
}

void
reset_room ()
{
  ::reset_room();
}

void
create_khalakhor_room()
{
  set_xlong("The fishing village of SaMorgan continues to the south "+
            "and to the west, and the trees to the north are getting "+
            "cleared out of the way. A tower has been constructed at "+
            "the northeastern point of the village.\n");
  config_room("northern");
  add_item("southwest", "There is a building in that direction.\n");
  add_item(({"west", "south"}),
           "The street continues in that direction.\n");
  add_item(({"east", "northeast", "southeast"}),
           "A rocky beach is in that direction.\n");
  add_item("north", "A road is being built in that direction.\n");
  add_item("northeast", "There is a tower in that direction.\n");
  add_item(({"tower", "guard tower"}),
           "A two-level guard tower has been constructed at the "+
           "northeastern point of the village.\n");
 
  add_exit("vil0208", "west");
  add_exit("vil0309", "south");
  add_exit("tower-ne", "northeast");
	
  add_fail("north", "The road is not ready yet, but keep on checking.\n");
  add_fail(({"southwest", "northwest"}),
           "There is a building blocking your way.\n");
  add_fail(({"east", "southeast"}),
           "Rocks block the way.\n");
  reset_worker_team(4);
}
