/*
 * Daenbraigh smithy
 * TAPAKAH, 09/2005
 */

#pragma strict_types

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h";

#include "../../daenbraigh.h";
#include "../../village/village.h";

inherit "/d/Khalakhor/std/room";
inherit DAENBRAIGH_BASE;

void
create_khalakhor_room()
{
  set_short(VILLAGE_NAME + " smithy");
  set_long("The smithy is set by a renegade dwarf. There is a plaque "+
	   "on the wall.\n");

  add_item(({"plaque","sign"}),
	   "You can repair your weapons here, if the smith is present.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("ns_2","west");
  add_npc(V_SMITH,
	  1,
	  &->equip_me());
  reset_room();
}

void
reset_room() {

  ::reset_room();

}

int *
query_local_coords()
{
  return ({-4,-2});
}
