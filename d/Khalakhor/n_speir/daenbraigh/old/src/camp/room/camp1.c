/* File         : /d/Khalakhor/n_speir/daenbraigh/camp/rooms/camp1.c
 * Creator      : Serpine@Genesis
 * Copyright    : All rights given to Genesis
 * Date         : 11 July 2008
 * Purpose      : 
 * Related files:
 * Comments     : 
 * Modifications:
 */

#pragma strict_types;

#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";
#include "/d/Khalakhor/sys/terrain.h";

#include "../../daenbraigh.h";
#include "../../camp/camp.h";
#include "../../village/village.h";

inherit "/d/Khalakhor/std/room";
inherit DAENBRAIGH_BASE;


void
create_khalakhor_room()
{
  ::create_khalakhor_room();

  set_short("Barricaded entrance to camp\n");
  set_long("* Some goblin guards and a breakable barricade blocking east *)\n");

  add_exit("camp_path_1",         "east");
  add_exit(V_ROOM + "ns_1", "west");
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
query_local_coors()
{
  return ({-4,-4});
}
