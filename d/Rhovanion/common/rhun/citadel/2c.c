
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel passage");
    set_long("You walk down a passage of black stone in this "+
	"dark citadel.  The marble floor turns here, allowing you "+
	"to travel to the north or west.\n");
	
    AE(RHUN+"citadel/2d","north");
    AE(RHUN+"citadel/2b","west");

    IN;
}

