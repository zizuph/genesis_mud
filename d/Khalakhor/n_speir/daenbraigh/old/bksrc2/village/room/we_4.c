/*
 * Village road west-east, #4
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
	      "to the south, in the east the forest starts and the path goes towards " +
              "the center of the village in the west. " + "@@query_garbage_desc"));
  add_exit(HHPATH + "path1","east",0);
  add_exit("we_3","west",0);
  add_exit("tower_e","north",0);
  add_exit("hut4","south",0);

  add_prop(GV_OUTSIDE,4);
  set_terrain(TERRAIN_ROAD);
  reset_room();
}
void
init()
{
  ::init();
}
