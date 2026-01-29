
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Seaside");
    set_long("The sand is soft and lightly colored here.  You "+
	"trudge along the beach, which leads off to the north "+
	"and southwest.\n");
	
    AE(RHUN+"hills/s17", "southwest");
    AE(RHUN+"hills/s15", "north");
    
    add_item(({"beach","sand"}), 
        "The sandy beach leads away from here "+
	"to the north and southwest.\n");
}
