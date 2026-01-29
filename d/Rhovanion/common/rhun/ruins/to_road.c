
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{   
    set_short("Edge of the ruins");
    set_long("You stand on the a wide dirt road at the northeast "+
    "edge of an area of stone ruins.  You may head down amongst "+
    "the ruins by heading southwest, or move back up the road "+
    "to the northeast.\n");
    
    AE(RHUN+"ruins/far_ne","southwest");
    AE(RHUN+"roads/section9/d","northeast");
    
    add_item(({"stone", "stones", "ruins", "rubble"}),
	"The stones which stand "+
	"near to here are the fallen remains of what was "+
	"perhaps once a great building or shrine of some sort.  They "+
	"appear quite heavy, and are of no real interest.\n");
}
