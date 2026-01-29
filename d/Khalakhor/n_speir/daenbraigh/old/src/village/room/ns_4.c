/*
 * Village road north-south #4
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

  set_long(query_long() + " There are huts on the both sides of the road, " +
	   "to the south the way ends before a watchtower and the path "    +
	   "goes towards the center of the village in the north. "          +
	   "@@query_garbage_desc");

  add_exit("hut8","east",0);
  add_exit("hut7","west",0);
  add_exit("ns_3","north",0);
  add_exit("tower_s","south",0);

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
  return ({-5,4});
}
