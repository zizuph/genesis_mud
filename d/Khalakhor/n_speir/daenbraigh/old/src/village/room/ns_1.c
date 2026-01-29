/*
 * Village road north-south #1
 * TAPAKAH 04/2005
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "../../camp/camp.h"

inherit V_ROAD_BASE;
inherit DAENBRAIGH_BASE;

void
create_khalakhor_room()
{
  ::create_gvillage_road();

  set_long(query_long() + " There is a watchtower the north and a hut "  +
	   "to the west, to the east you can see a military camp "       +
	   "and the path goes towards the center of the village in the " +
	   "south. " + "@@query_garbage_desc");

  add_exit(C_ROOM + "camp1","east",0);
  add_exit("hut9","west",0);
  add_exit("tower_n","north",0);
  add_exit("ns_2","south",0);

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
  return ({-5,-4});
}
