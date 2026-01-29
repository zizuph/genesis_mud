/*
 * Village road north-south #3
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
	      "to the south it is getting duller " +
	      "and the path goes towards the center of the village in the north. " +
	      "@@query_garbage_desc"));
  add_exit("hut6","east",0);
  add_exit("hut5","west",0);
  add_exit("ns_4","south",0);
  add_exit("crossing","north",0);

  add_prop(GV_OUTSIDE,7);
  set_terrain(TERRAIN_ROAD);
  reset_room();
}
void
init()
{
  ::init();
}
