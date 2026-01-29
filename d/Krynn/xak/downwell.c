/* Xak Tsorath coded by Percy */

#include "xlocal.h"
inherit  XAKINROOM
#include "/sys/ss_types.h"
#include <macros.h>

void
create_xak_room()
{
    set_short("Down a dark well");
    set_long("The ladder goes down a few feet and then the well seems to"
	     + " break off and you see it enter through the roof of a huge"
	     + " underground cavern. It isn't possible to go down any further"
	     + " unless you can fly the several hundred feet to the cavern floor"
	     + " below.\n");
    
    add_exit(TDIR + "square.c", "up", 0);
    INSIDE;
    DARK;
}

