/*
 * Village road west-east, #3
 * TAPAKAH 04/2005
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"

inherit V_ROAD_BASE;
inherit DAENBRAIGH_BASE;

void
create_khalakhor_room()
{
  ::create_gvillage_road();

  set_long(query_long() + " There are ordinary huts to the north and "  +
	   "to the south, while the path leads from the forest in the " +
	   "east towards the center of the village in the west. "       +
	   "@@query_garbage_desc");

  add_exit("we_4","east",0);
  add_exit("crossing","west",0);
  add_exit("hut1","north",0);
  add_exit("hut3","south",0);

  ::complete_creation();

}

void
init()
{
  ::init();
}

int *
query_local_coords()
{
  return ({-4,0});
}
