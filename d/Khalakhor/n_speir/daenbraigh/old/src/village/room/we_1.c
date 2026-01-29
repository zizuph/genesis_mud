/*
 * Village road west-east, #1
 * TAPAKAH 04/2005
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "../../pier/pier.h"

inherit V_ROAD_BASE;
inherit DAENBRAIGH_BASE;

void
create_khalakhor_room()
{
  ::create_gvillage_road();

  set_long(query_long() + " There is a watchtower to the north and a hut "  +
	   "to the south, while the path leads from the coast in the west " +
	   "towards the center of the village in the east. "                +
	   "@@query_garbage_desc@@");

  add_exit(PIER_ROOM + "pier4","west",0);
  add_exit("we_2","east",0);
  add_exit("tower_w","north",0);
  add_exit("hut2","south",0);

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
  return ({-7,0});
}
