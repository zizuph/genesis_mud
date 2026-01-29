// outpost/boat/sea1.c
// creator(s):  Kazz    April 1995
// last update:
// purpose:     water room for boat tween outpost & park
// note:	add_items are not needed since they can't be examined
//		from the deck.

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include "/d/Avenir/common/outpost/boat/ship.h"

void
create_room() {
    set_short("near the beach by a tunnel");
    set_long("The boat is near a sandy beach by a tunnel into the rock. "+
	     "The islands of the great sea are to the north.\n" );

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 1);
}  