/*
	coder(s):	Amelia
	history:
             25/5/95   adapted to inherit from standard tunnel  Maniac
             5/3/95    updated by Amelia
*/

#pragma save_binary

inherit "/d/Calia/std/std_lower_tunnel";

#include <stdproperties.h>
#include <macros.h>
#include "tun.h"

void
create_room()
{
	make_the_room("There is a ladder here that leads up " +
                      "to a chamber.\n");

        add_item("ladder", "The ladder is secured to "+
                "the wall, and leads up to a chamber above.\n");
        add_item("tunnel", "The tunnel runs a long way to the " +
                           "south from here.\n");

	add_exit(TUN+"tun1", "south", "@@travel_tunnel", 2);
	add_exit(TUN+"guard_room_W", "up", "@@up");
}

int
up()
{
	write("You climb the ladder.\n");
	say(QCTNAME(TP)+" climbs the ladder.\n");
	return 0;
}
