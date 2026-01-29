
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"


create_room()
{
    set_short("Citadel hallway");
	set_long(
        "You walk this dark hallway in the citadel.  No decorations "+
        "such as tapestries, paintings, or rugs can be seen here.  "+
        "There are signs that someone or something still resides "+
        "on the upper floors here, and that men of some kind still walk "+
        "the halls, though you know not whom, or for what purpose.\n");

    AE(RHUN+"citadel/3a","northeast");
    AE(RHUN+"citadel/3c","east");
    AE(RHUN+"citadel/3g","northwest");

    IN;
}

