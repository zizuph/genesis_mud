
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
	"one of the huts to the east or west, leave town back "+
	"to the south, or travel further up the dirt road "+
	"northward.\n");

    add_item(({"hut", "huts"}), "A few simple huts stand "+
	"nearby.  This town is rather small.  There are "+
	"huts here on the east and west sides of the road.\n");
    add_item("road", "The dirt road is quite simple and narrow.  "+
	"It heads further into the small town of Rhosgobel "+
	"to the north, and out of town to the south.\n");
	
    AE(RHOS+"hut_se", "east");
    AE(RHOS+"hut_sw", "west");
    AE(RHOS+"road2", "north");
    AE("SOMEWHERE", "south");
    
}
