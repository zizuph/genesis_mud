
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel passage");
    set_long("Magnificent walls of shining black stone rise up "+
	"around you as you travel down this hallway.  It leads "+
	"here from east to west.\n");

    AE(RHUN+"citadel/2e","east");
    AE(RHUN+"citadel/2g","west");

    IN;
}

