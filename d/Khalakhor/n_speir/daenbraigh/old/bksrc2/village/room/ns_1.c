/*
 * Village road north-south #1
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

  set_long(BS(query_long() + " There is a watchtower the north and a hut " +
	      "to the west, to the east you can see a military camp " +
	      "and the path goes towards the center of the village in the south. " +
	      "@@query_garbage_desc"));
  add_exit(CAMPPATH + "camp1","east",0);
  add_exit("hut9","west",0);
  add_exit("tower_n","north",0);
  add_exit("ns_2","south",0);

  add_prop(GV_OUTSIDE,5);
  set_terrain(TERRAIN_ROAD);
  reset_room();
}
void
init()
{
  ::init();
}
