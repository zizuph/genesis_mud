/**********************************************************************
 * - vil0501.c                                                      - *
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

public int *
query_local_coords()
{
  return ({5, 1});
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
  set_xlong("The fishing village of SaMorgan continues to the north, to the south and to the east, and the rocks to the west are getting cleared out of the way.\n");
  config_room("western");
  add_item(({"northeast", "southeast"}),
	   "There is a building in that direction.\n");
  add_item(({"east", "north", "south"}),
	   "The street continues in that direction.\n");
  add_item(({"southwest", "northwest"}),
	   "There is a rocky beach in that direction.\n");
  add_item(({"west"}),
	   "A road is being built in that direction.\n");
	
  add_exit("vil0401", "north");
  add_exit("vil0601", "south");
  add_exit("vil0502", "east");
	
  add_fail(({"west"}),
	   "The road is not ready yet, but keep on checking.\n");
  add_fail(({"southwest", "northwest"}),
	   "Rocks block your passage.\n");
  add_fail(({"northeast", "southeast"}),
	   "A building stops your passage.\n");
	
  set_alarm(0.5, 0.0, reset_room);
}
