/*
    Part of the lower guild tunnel of Mount Kyrus. 

    Coded by Maniac and Amelia, 

    copied over and adapted, Maniac, 5/3/96

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
        add_item("tunnel", "The tunnel runs a fair way to the " +
                           "northwest from here.\n");

	add_exit(TUN+"tun13", "northwest");
	add_exit(TUN+"guard_room_S", "up", "@@up");
}


int
up()
{
	write("You climb the ladder.\n");
	say(QCTNAME(TP)+" climbs the ladder.\n");
	return 0;
}
