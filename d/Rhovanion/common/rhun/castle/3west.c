
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Wide hallway");
    set_long("You are at the west end of a wide hallway.  It heads "+
	"back to the east from here.  There is also a guest suite "+
	"just to the northeast.\n");
			
    AE(RHUN+"castle/3north", "northeast");
    AE(RHUN+"castle/3stairs", "east");

    IN;
}
