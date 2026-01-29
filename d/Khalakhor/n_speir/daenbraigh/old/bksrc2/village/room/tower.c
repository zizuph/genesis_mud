/*
 * Tower - first floor
 * TAPAKAH, 04/2005
 */

#pragma strict_types
inherit "/d/Khalakhor/std/room";

#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
#include "../../nspeir.h"
#include "../../village/village.h"

void
create_gvillage_tower(string floor)
{
  ::create_khalakhor_room();

  set_short(capitalize(floor) + " floor of a tower in " + VILLAGENAME);
  set_long(BS("You are on the " + floor + " floor of a tower guarding the village of " +
	      VILLAGENAME + ". The room is quite spartan, with a table and a few stools."+
	      " The windows in all of the four walls, protected with iron bars, provide "+
	      "a good view on what is going on outside."));

  add_item(({"table"}),
	   "A simple wooden table with a few plates and cups on it.\n");
  add_item(({"stool","stools"}),
	   "Plain stools, made of wood.\n");
  add_item(({"plate","cup","plates","cups"}),
	   "Earthen-made dishes contain some food leftovers.\n");
  add_item(({"window","windows","bars","bar","wall","walls"}),
	   "Walls, made from thick wooden logs, have a window in each one of them.\n"+
	   "Each window provides a view on activities outside the tower.\n");
  add_item(({"view"}),
	   "@@query_view@@");
  add_prop(GV_OUTSIDE,0);
  add_prop(ROOM_I_INSIDE,1);
  reset_room();
}
void
init()
{
  ::init();
}
string
query_view()
{
}
