/*
 * Tower - base file
 * TAPAKAH, 04/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"

inherit "/d/Khalakhor/std/room";

void
create_gvillage_tower(string floor)
{
  ::create_khalakhor_room();

  set_short(capitalize(floor) + " floor of a tower in " + VILLAGE_NAME);
  set_long("You are on the " + floor + " floor of a tower guarding the  "    +
	   "village of " + VILLAGE_NAME + ". The room is quite spartan, "    +
	   "with a table and a few stools. The windows in all of the four "  +
	   "walls, protected with iron bars, provide a good view on what is "+
	   "going on outside.\n");

  add_item(({"table"}),
	   "A simple wooden table with a few plates and cups on it.\n");
  add_item(({"stool","stools"}),
	   "Plain stools, made of wood.\n");
  add_item(({"plate","cup","plates","cups"}),
	   "Earthen-made dishes contain some food leftovers.\n");
  add_item(({"window","windows","bars","bar","wall","walls"}),
	   "Walls, made from thick wooden logs, have a window in each one "+
	   "of them. Each window provides a view on activities outside the "+
	   "tower.\n");
  add_item(({"view"}),
	   "@@query_view@@");
  add_prop(ROOM_I_INSIDE,1);
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
