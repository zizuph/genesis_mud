/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("The old larder");
        set_long(BS(
           "This room looks like it may once have been a larder of some sort."
	 + " It is now bare and empty.", 70));

	add_exit(DDIR + "liftbottom.c", "south", 0);

	INSIDE
        DARK
}

