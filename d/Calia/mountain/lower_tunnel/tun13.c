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
	make_the_room("\n");

        add_item(({"tunnel"}), "The tunnel extends north " +
                               "and southeast.\n");
	add_exit(TUN+"tun12", "north");
	add_exit(TUN+"tun14", "southeast");
}
