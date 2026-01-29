
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Cavernous basement");
    set_long("You are in a cavernous basement beneath the ruined "+
	"stone castle.  Stone steps lead upward here, back to the "+
	"castle's main floor.  This chamber is very wide, though "+
	"not especially tall.  The walls are not manmade, but instead "+
	"seem to have been hewed naturally, or perhaps by some magic "+
	"force.  The cavern continues to the north.\n");

    add_item(({"stairs", "stairway", "staircase", "stair"}), 
	"The stairs are narrow, and head upward from here.\n");
	
    AE(RHUN+"castle/guardroom","north");
    AE(RHUN+"castle/stairs0","up");

    IN;
}

