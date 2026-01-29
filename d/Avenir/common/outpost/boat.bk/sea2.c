// outpost/boat/sea2.c
// creator(s):  Kazz    April 1995
// last update:
// purpose:     water room for boat tween outpost & park
// note:	add_items are not needed since they can't be examined
//		from the ship deck.

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include "/d/Avenir/common/outpost/boat/ship.h"

void
create_room()
{
  set_short("between outpost tunnel and islands");
  set_long("You float on the great cavern sea between a wall with a "+
	   "tunnel and islands in the sea.\n" );

  add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
  add_prop(ROOM_I_INSIDE,1);
}  