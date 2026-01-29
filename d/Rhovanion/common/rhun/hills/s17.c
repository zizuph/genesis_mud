
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Seaside");
    set_long("You stand at the south end of a long beach on "+
	"the west side of the Sea of Rhun.  To the west, a path "+
	"begins to climb up into the hills and mountains that "+
	"lie in that direction.  The beach continues to the "+
	"northeast.\n");
	
    AE(RHUN+"hills/p1", "west");
    AE(RHUN+"hills/s16", "northeast");
    
    add_item("beach", "The sandy beach leads away from here "+
	"to the northeast.\n");
    add_item(({"hill", "hills", "mountain", "mountains"}), 
	"Many high hills and mountains stand together just "+
	"to the west.  A dark cloud seems to hang perpetually "+
	"over them.\n");
}
