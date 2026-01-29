/*
 * Village road north-south #4
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

  set_long(BS(query_long() + " There are huts on the both sides of the road, " +
	      "to the south the way ends before a watchtower " +
	      "and the path goes towards the center of the village in the north. " +
	      "@@query_garbage_desc"));
  add_exit("hut8","east",0);
  add_exit("hut7","west",0);
  add_exit("ns_3","north",0);
  add_exit("tower_s","south",0);

  add_prop(GV_OUTSIDE,8);
  set_terrain(TERRAIN_ROAD);
  reset_room();
}
void
init()
{
  ::init();
}
