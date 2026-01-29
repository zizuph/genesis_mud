
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{   
    set_short("Edge of the ruins");
    set_long("A few scattered stones lay here, remnants of what "+
    "was perhaps once a great building or shrine, which now has "+
    "been laid to rest and is little more than piles of dirt and rubble.  "+
    "You stand on the edge of this area, with the ruins continuing "+
    "around you to the "+
    "southwest and southeast"+
    ".\n");
    
    AE(RHUN+"ruins/far_nw","southwest");
    AE(RHUN+"ruins/far_ne","southeast");
    
    add_item(({"stone", "stones", "ruins", "rubble"}),
	"The stones which stand "+
	"near to here are the fallen remains of what was "+
	"perhaps once a great building or shrine of some sort.  They "+
	"appear quite heavy, and are of no real interest.\n");
}
