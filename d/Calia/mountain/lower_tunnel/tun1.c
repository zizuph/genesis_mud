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
	make_the_room("\n");

        add_item(({"tunnel"}), "The tunnel extends north and south.\n");
	add_exit(TUN+"tun2", "south", "@@travel_tunnel", 2);
	add_exit(TUN+"tun0", "north", "@@travel_tunnel", 2);
}
