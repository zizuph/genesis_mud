
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{   
    set_short("Among the ruins");
    set_long("Large fallen stones and other remains surround you as "+
	"you make your way through these ruins.  You wonder what kind "+
	"of building or shrine stood here; for now the stones have "+
	"fallen and withered away.  The piles of stone blocks and "+
	"rubble continue to the north, and a narrow dirt path leads "+
	"south from here.  You may also approach the center of this "+
	"rocky, ruinous area by going northeast.  To the west is the "+
	"sound of the sea, where the Sea of Rhun beats upon its sandy "+
	"eastern shore.\n");
    
    AE(RHUN+"ruins/w_side", "north");
    AE(RHUN+"ruins/to_hag", "south");
    AE(RHUN+"ruins/center", "northeast");
    AE(RHUN+"ruins/seashore3", "west");
    
    add_item(({"stone", "stones", "ruins", "rubble"}),
	"The stones which stand "+
	"near to here are the fallen remains of what was "+
	"perhaps once a great building or shrine of some sort.  They "+
	"appear quite heavy, and are of no real interest.\n");
}
