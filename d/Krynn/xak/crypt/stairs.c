/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("The paths of the dead");
        set_long(BS(
           "You have entered a small square chamber in the centre"
	 + " of which is a spiral staircase that leads up to the"
	 + " temple complex above. The stairway is aptly known as the paths"
    + " of the dead. A pedestal rises up the centre of the"
	 + " staircase.", 70));

	add_exit(CDIR + "entry.c", "east", 0);
	add_exit(TDIR + "tempstairs.c", "up", "@@up");

        add_item("pedestal", "A simple stone column rising through the" +
			" centre of the stairway.\n");

	INSIDE
        DARK
}

int
up()
{
	write("You climb up the dark stairway.\n");
	return 0;
}








