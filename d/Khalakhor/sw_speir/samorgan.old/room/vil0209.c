/**********************************************************************
 * - vil0209.c                                                      - *
 * - Village room.                                                  - *
 * - Created by Damaris@Genesis 02/2005                             - *
 * - Slightly modified for future developments by Tapakah, 04/2021  - *
 **********************************************************************/
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit SAMORGAN_BASE;
inherit UTILS;

/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/

public int *
query_local_coords()
{
  return ({2, 9});
}

public int *
query_global_coords()
{
  return SAMORGAN_COORDS;
}

public void
reset_room ()
{
  ::reset_room();
  reset_worker_team(4);
}

void
create_khalakhor_room()
{
  set_xlong("The fishing village of SaMorgan continues to the south and to the west, and the trees to the north are getting cleared out of the way.\n");
  config_room("northern");
  add_item(({"southwest", "northwest"}),
	   "There is a building in that direction.\n");
  add_item(({"west", "south"}),
	   "The street continues in that direction.\n");
  add_item(({"east", "northeast", "southeast"}),
	   "A rocky beach is in that direction.\n");
  add_item(({"north"}),
	   "A road is being built in that direction.\n");
  
  add_exit("vil0208", "west");
  add_exit("vil0309", "south");
	
  add_fail(({"north"}),
	   "The road is not ready yet, but keep on checking.\n");
  add_fail(({"southwest", "northwest"}),
	   "There is a building blocking your way.\n");
  add_fail(({"northeast", "east", "southeast"}),
	   "Rocks block the way.\n");
  set_alarm(0.5, 0.0, reset_room);
}
