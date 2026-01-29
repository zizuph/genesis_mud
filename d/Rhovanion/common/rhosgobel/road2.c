
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Town road");
    set_long("You walk along a dirt road, little more than a "+
	"path, in the small town of Rhosgobel.  A few huts "+
	"line the streets here.  This is the home of the "+
	"wizard Radagast the Brown.  The people here are "+
	"wary of you, of any strangers.  You can head into "+
	"one of the huts to the east or west, or go back "+
	"to the southern part of town.  There is also a "+
	"larger building to the north, at the head of "+
	"Rhosgobel.\n");

    add_item(({"hut", "huts"}), "A few simple huts stand "+
	"nearby.  This town is rather small.  There are "+
	"huts here on the east and west sides of the road.\n");
    add_item("road", "The dirt road is quite simple and narrow.  "+
	"It heads further into the small town of Rhosgobel "+
	"to the south.\n");
    add_item("building", "The larger building, just north of "+
	"here, must be the home of the wizard Radagast.\n");
	
    AE(RHOS+"hut_ne", "east");
    AE(RHOS+"hut_nw", "west");
    AE(RHOS+"road1", "south");
    AE(RHOS+"rad_hut", "north");
    
}
