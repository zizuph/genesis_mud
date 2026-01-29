/*
 * Village road west-east, #1
 * TAPAKAH 04/2005
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"
#include "../../nspeir.h"
#include "../../village/village.h"

inherit VROOM + "road";

void
create_khalakhor_room()
{
  ::create_gvillage_road();

  set_long(BS(query_long() + " There is a watchtower to the north and a hut to the "+
	      "south, while the path leads from the coast in the west towards the "+
	      "center of the village in the east. " + "@@query_garbage_desc"));
  add_exit(PIERPATH + "pier1","west",0);
  add_exit("we_2","east",0);
  add_exit("tower_w","north",0);
  add_exit("hut2","south",0);

  add_prop(GV_OUTSIDE,1);
  set_terrain(TERRAIN_ROAD);
  reset_room();
}
void
init()
{
  ::init();
}
