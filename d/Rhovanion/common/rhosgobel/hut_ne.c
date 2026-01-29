
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"
#include <stdproperties.h>

create_room()
{
    set_short("Hut");
    set_long("This is a simple hut, the home of some of the "+
	"simple people of Rhosgobel.  It is sparsely furnished.  "+
	"Really,  there's nothing very interesting here.  The "+
	"only exit is the door leading back to the west.\n");

    AE(RHOS+"road2", "west");
    
    IN;
    
}
