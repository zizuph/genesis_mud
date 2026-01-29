/*
 * Village road north-south #2
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

  set_long(BS(query_long() + " There is a shabby pub to the west, " +
	      "to the east you hear the clanking of the local smith, " +
	      "to the north you see more people with a military look " +
	      "and the path goes towards the center of the village in the south. " +
	      "@@query_garbage_desc"));
  add_exit("smithy","east",0);
  add_exit("pub","west",0);
  add_exit("ns_1","north",0);
  add_exit("crossing","south",0);

  add_prop(GV_OUTSIDE,6);
  set_terrain(TERRAIN_ROAD);
  reset_room();
}
void
init()
{
  ::init();
}
