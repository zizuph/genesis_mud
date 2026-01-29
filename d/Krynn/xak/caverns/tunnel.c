/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("A natural tunnel");
        set_long(BS(
           "You are in a large natural underground tunnel. The walls are of hard"
	 + " stone, yet in places appears to be perfectly smooth. You wonder"
	 + " what could have caused such smoothing. The tunnel exit is"
	 + " hidden by a waterfall to the east and the tunnel continues to"
	 + " the south.", 70));

	add_exit(DDIR + "fall.c", "east", 0);
	add_exit(DDIR + "cavernentry.c", "south", 0);

	add_item(({"tunnel", "walls", "wall"}), "@@wall");

	INSIDE
        DARK
}

wall()
{
	write("It appears to be a huge natural tunnel, except for the strange"
	 + " smooth patches.\n");
	return "";
}
