/*
 * Village crossing
 * TAPAKAH 05/2005
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"

inherit "/d/Khalakhor/std/room";
inherit DAENBRAIGH_BASE;

void
create_khalakhor_room()
{
  ::create_khalakhor_room();

  set_short("Central crossing of " + VILLAGE_NAME);
  set_long("You are standing on the crossing of two paths inside "         +
	   VILLAGE_NAME + ". You hear snow and ice crust croaking under "  +
	   "your feet. It is quite cold and the wind is blowing strongly. "+
	   "This place looks important as it is very clean and a tent is " +
	   "standing in the center of the crossing.\n");

  add_exit("we_2","west",0);
  add_exit("we_3","east",0);
  add_exit("ns_2","north",0);
  add_exit("ns_3","south",0);
  add_exit("tent","tent",0);

  add_item("tent",
	   "This tall tent is probably a residence of someone "+
	   "rather important, as it is exceptionally clean, and is set "+
	   "right in the middle of the settlement.\n");
  add_prop(ROOM_I_INSIDE,0);
  set_terrain(TERRAIN_ROAD);
  reset_room();
}

void
init()
{
  ::init();
}

void
reset_room()
{
  ::reset_room();
}

int *
query_local_coords()
{
  return ({-5,0});
}
