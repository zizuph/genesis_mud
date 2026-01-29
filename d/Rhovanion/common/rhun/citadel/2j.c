
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel passage");
    set_long("You walk down a passage on the second floor of this "+
	"dark citadel.  The entire estate seems void of decoration, "+
	"dreary in a way.  The dark marble floor leads toward a "+
	"stairwell to the northeast, and also off to the north.\n");

    AE(RHUN+"citadel/2k","northeast");
    AE(RHUN+"citadel/2i","north");

    IN;
}

