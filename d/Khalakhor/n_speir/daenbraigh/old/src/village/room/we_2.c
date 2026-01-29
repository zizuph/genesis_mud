/*
 * Village road west-east, #2
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

  set_long(query_long() + " The village shop is to the north and a post " +
	   "office is to the south, while the path leads from the coast " +
	   "in the west towards the center of the village in the east. "  +
	   "@@query_garbage_desc");

  add_exit("we_1","west",0);
  add_exit("crossing","east",0);
  add_exit("shop","north",0);
  add_exit("poffice","south",0);

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
  return ({-6,0});
}
