/* File         : /d/Khalakhor/n_speir/daenbraigh/camp/rooms/camp_path_3.c
 * Creator      : Serpine@Genesis * Copyright    : All rights given to Genesis
 * Date         : 12 July 2008
 * Purpose      : 
 * Related files:
 * Comments     : 
 * Modifications:
 */

/* ------------------------------------------------------------------------- */

#pragma strict_types;
#include <stdproperties.h>
#include <macros.h>

#include "/d/Khalakhor/sys/defs.h";
#include "/d/Khalakhor/sys/terrain.h";
#include "../../daenbraigh.h";
#include "../../camp/camp.h";

inherit "/d/Khalakhor/std/room";
inherit DAENBRAIGH_BASE;

void
create_khalakhor_room()
{
  ::create_khalakhor_room();

  set_short("Western section of northern camp path\n");
  set_long("* Long description *\n");

  add_exit("camp_path_4", "east", 0,0,0);
  add_exit("camp_path_2", "southwest", 0,0,0);
  add_exit("camp_watch_1", "west", 0,0,0);

  add_item({"tower", "watchtower", "platform", "wooden platform"}), (
    "More just an enclosed wooden platform, it is unclear from this position if "
   +"it is currently inhabited or not.\n");

  add_item({"tent", "command tent", "command tents", "small tent", "small tents"}), (
    "Sewn together from the hides of various animals... among other things.\n");

  add_item(({ "spike", "spikes" "wooden spike", "wooden spikes" }), (
    "They look extremely sharp.\n");

  add_item(({ "path", "perimeter" }), (
    "It is well traveled, as if by frequent patrol.\n");

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
  return ({-1,2});
}
