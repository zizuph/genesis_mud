
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{   
    set_short("Among the ruins");
    set_long("You wander amongst the ruins of what was once some great "+
	"building or shrine.  All about stand piles of rubble and heavy "+
	"blocks of white or light-grey colored stone.  The area's "+
	"center stands just to the south, while you may also travel "+
	"among the fallen stones to the north, west or east.\n");
    
    AE(RHUN+"ruins/ne_side", "east");
    AE(RHUN+"ruins/center", "south");
    AE(RHUN+"ruins/nw_side", "west");
    AE(RHUN+"ruins/far_nw", "north");
    
    add_item(({"stone", "stones", "ruins", "rubble"}),
	"The stones which stand "+
	"near to here are the fallen remains of what was "+
	"perhaps once a great building or shrine of some sort.  They "+
	"appear quite heavy, and are of no real interest.\n");
}
