
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel passage");
    set_long("Magnificent walls of shining black stone rise up "+
	"around you as you travel down this hallway.  It leads "+
	"here from east to west, while a low archway leads into "+
	"a stairwell to the southeast.\n");

    AE(RHUN+"citadel/2f","east");
    AE(RHUN+"citadel/2h","west");
    AE(RHUN+"citadel/2a", "southeast");

    IN;
}

