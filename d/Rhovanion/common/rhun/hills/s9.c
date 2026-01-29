
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Seaside");
    set_long("You find yourself walking along the sandy beach "+
	"that is the western edge of the Sea of Rhun.  The "+
	"lightly colored sand stretched away to the south and "+
	"northeast.\n");
	
    AE(RHUN+"hills/s8", "northeast");
    AE(RHUN+"hills/s15", "south");
    
    add_item(({"beach","sand"}), 
        "The sandy beach leads away from here "+
	"to the northeast and south.\n");
}
