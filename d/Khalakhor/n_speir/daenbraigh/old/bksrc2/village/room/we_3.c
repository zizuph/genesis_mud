/*
 * Village road west-east, #3
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

  set_long(BS(query_long() + " There are ordinary huts to the north and " +
	      "to the south, while the path leads from the forest in the east towards " +
              "the center of the village in the west. " + "@@query_garbage_desc"));
  add_exit("we_4","east",0);
  add_exit("crossing","west",0);
  add_exit("hut1","north",0);
  add_exit("hut3","south",0);

  add_prop(GV_OUTSIDE,3);
  set_terrain(TERRAIN_ROAD);
  reset_room();
}
void
init()
{
  ::init();
}
