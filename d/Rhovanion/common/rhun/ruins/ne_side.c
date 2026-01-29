
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{   
    set_short("Among the ruins");
    set_long("Large fallen stones and other remains surround you as "+
	"you make your way through these ruins.  You wonder what kind "+
	"of building or shrine stood here; for now the stones have "+
	"fallen and withered away.  The piles of stone blocks and "+
	"rubble continue to the south, northeast and west from here. "+
	" You may also approach the center of this "+
	"rocky, ruinous area by going southwest.\n");
    
    AE(RHUN+"ruins/far_ne", "northeast");
    AE(RHUN+"ruins/e_side", "south");
    AE(RHUN+"ruins/center", "southwest");
    AE(RHUN+"ruins/n_side", "west");
    
    add_item(({"stone", "stones", "ruins", "rubble"}),
	"The stones which stand "+
	"near to here are the fallen remains of what was "+
	"perhaps once a great building or shrine of some sort.  They "+
	"appear quite heavy, and are of no real interest.\n");
}
