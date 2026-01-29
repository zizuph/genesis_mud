
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{   
    set_short("Among the ruins");
    set_long("You wander amongst the ruins of what was once some great "+
	"building or shrine.  All about stand piles of rubble and heavy "+
	"blocks of white or light-grey colored stone.  The area's "+
	"center stands just to the north, while you may also travel "+
	"among the fallen stones to the south or east.\n");
    
    AE(RHUN+"ruins/se_side", "east");
    AE(RHUN+"ruins/s_end", "south");
    AE(RHUN+"ruins/center", "north");
    
    add_item(({"stone", "stones", "ruins", "rubble"}),
	"The stones which stand "+
	"near to here are the fallen remains of what was "+
	"perhaps once a great building or shrine of some sort.  They "+
	"appear quite heavy, and are of no real interest.\n");
}
