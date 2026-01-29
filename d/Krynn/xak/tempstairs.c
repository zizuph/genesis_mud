/* Xak Tsorath coded by Percy */

#include "xlocal.h"

inherit XAKINROOM

#include <ss_types.h>
#include <macros.h>

void
create_xak_room()
{
    set_short("The paths of the dead");
    set_long("You have entered a small square chamber in the centre"
	     + " of which is a spiral staircase that leads down to the"
	     + " crypts below. The stairway is aptly known as the paths"
	     + " of the dead. A pedestal rises up the centre on the"
	     + " staircase.\n");
    
    add_exit(TDIR + "tempchamber.c", "west", 0);
    add_exit(CDIR + "stairs.c", "down", "@@down");
    
    add_item("pedestal", "A simple stone column rising through the" +
	     " centre of the stairway.\n");
    
    INSIDE;
    DARK;
}

int
down()
{
    write("You decend down the dark stairway.\n");
    return 0;
}
