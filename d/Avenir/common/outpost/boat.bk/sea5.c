// outpost/boat/sea5.c
// creator(s):  Boriska    Sep 1995
// last update:
// purpose:     water room for boat between outpost & park
// note:	add_items are not needed since they can't be examined
//		from the ship deck.

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include "/d/Avenir/common/outpost/boat/ship.h"

void
create_room()
{
  set_short("on the sea, close to shore");
  set_long("Very close is an island covered with grass and trees, "+
	   "elsewhere is just the sea and great cavern.\n" );
  add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
  add_prop(ROOM_I_INSIDE, 1);
}  