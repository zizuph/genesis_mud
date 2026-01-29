/*
 * Village road north-south #2
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

  set_long(query_long() + " There is a shabby pub to the west, to the "   +
	   "east you hear the clanking of the local smith, to the north " +
	   "you see more people with a military look and the path goes "  +
	   "towards the center of the village in the south. " +
	   "@@query_garbage_desc");

  add_exit("smithy","east",0);
  add_exit("pub","west",0);
  add_exit("ns_1","north",0);
  add_exit("crossing","south",0);

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
  return ({-5,-2});
}
