
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Castle entryway");
    set_long("The entryway of this castle, a long, narrow room, "+
	"is decorated with a few old rugs and tapestries, though "+
	"they have been worn away by the passage of time.  The "+
	"walls are of grey stone, crumbled a bit in places.  A "+
	"large doorway heads north, further into this ruined castle, "+
	"while the place where the gate once stood is just to the "+
	"south from here.\n");

    add_item(({"rug", "rugs", "tapestry", "tapestries", "decoration", 
	"decorations"}), "The rugs and tapestries that decorate "+
	"this entryway were once very fine and colorfully beautiful."+
	"  The passage of time has left little behind of them that "+
	"is discernible.\n");
    add_item(({"wall", "walls", "stone", "stones", "grey stone"}), 
	"The walls here are made of a light-grey stone.  They have "+
	"begun to crumble in places, due to natural entropy and the "+
	"passage of time.\n");
    add_item(({"doorway", "north", "door", "large doorway", 
	"north doorway"}), "A large doorway in the stone leads "+
	"north from here, heading further toward the center of this "+
	"ruined castle.\n");

    AE(RHUN+"castle/cross","north");
    AE(RHUN+"castle/entry","south");

    IN;
}

