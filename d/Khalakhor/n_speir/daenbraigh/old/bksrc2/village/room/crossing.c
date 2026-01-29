/*
 * Village crossing
 * TAPAKAH 05/2005
 */

#pragma strict_types

inherit "/d/Khalakhor/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"
#include "../../nspeir.h"
#include "../../village/village.h"

object tent;
void
create_khalakhor_room()
{
  ::create_khalakhor_room();

  set_short("Central crossing of " + VILLAGENAME);
  set_long(BS("You are standing on the crossing of two paths inside " + VILLAGENAME + " "+
	   "You hear snow and ice crust croaking under your feet. It is quite "+
	   "cold and the wind is blowing strongly. This place looks important as it "+
	   "is very clean and a tent is standing in the center of the crossing."));
  add_exit("we_2","west",0);
  add_exit("we_3","east",0);
  add_exit("ns_2","north",0);
  add_exit("ns_3","south",0);
  add_exit("tent","enter",0);
  add_prop(ROOM_I_INSIDE,0);
  add_prop(GV_OUTSIDE,9);
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
  if(!tent) {
    tent = clone_object(TENT);
    tent->move(TO);
  }
}
