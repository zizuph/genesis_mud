
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{   
    set_short("Among the ruins");
    set_long("Large fallen stones and other remains surround you as "+
	"you make your way through these ruins.  You wonder what kind "+
	"of building or shrine stood here; for now the stones have "+
	"fallen and withered away.  The piles of stone blocks and "+
	"rubble continue to the south, northeast and east from here. "+
	" You may also approach the center of this "+
	"rocky, ruinous area by going southeast.  To the west is the "+
	"sound of the sea, where the Sea of Rhun beats upon its sandy "+
	"eastern shore.\n");
    
    AE(RHUN+"ruins/far_nw", "northeast");
    AE(RHUN+"ruins/w_side", "south");
    AE(RHUN+"ruins/n_side", "east");
    AE(RHUN+"ruins/seashore1", "west");
    AE(RHUN+"ruins/center","southeast");
    
    add_item(({"stone", "stones", "ruins", "rubble"}),
	"The stones which stand "+
	"near to here are the fallen remains of what was "+
	"perhaps once a great building or shrine of some sort.  They "+
	"appear quite heavy, and are of no real interest.\n");
}
