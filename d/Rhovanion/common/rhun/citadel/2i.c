
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Citadel passage");
    set_long("This black stone passage continues, leading from "+
	"north to south.\n");
	
    AE(RHUN+"citadel/2h","north");
    AE(RHUN+"citadel/2j","south");

    IN;
}

