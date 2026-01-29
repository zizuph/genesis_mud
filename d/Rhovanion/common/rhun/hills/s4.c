
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Seaside");
    set_long("You are near to the northwest corner of the Sea "+
	"of Rhun.  A beach of warm, lightly-coloured sand "+
	"stretches out here from north to southwest.\n");
	
    AE(RHUN+"hills/s3", "north");
    AE(RHUN+"hills/s8", "southwest");
    
    add_item(({"beach","sand"}), 
        "The sandy beach leads away from here "+
	"to the north and southwest.\n");
}
