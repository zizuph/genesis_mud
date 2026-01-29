/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit XAKINROOM

create_xak_room()
{
        set_short("A not so natural tunnel");
        set_long(BS(
           "You are in a large underground tunnel. The walls are of hard"
	 + " stone, yet here they are perfectly smooth. You wonder"
	 + " what could have caused such smoothing. You can see the tunnel"
	 + " enters south into another huge cavern beyond. You feel a great danger"
	 + " and an unreasoned fear of going that way.", 70));

	add_exit(DDIR + "tunnel.c", "north", 0);
	add_exit(DDIR + "cavern.c", "south", 0);

	add_item(({"tunnel", "walls", "wall"}), "@@wall");

	INSIDE
        DARK
}

wall()
{
	write("It appears to be a huge natural tunnel, except the walls"
	 + " are amazingly smooth as if eaten away by some powerful acid...\n");
	return "";
}
