
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{   
    set_short("Small dirt path");
    set_long("You walk among the fallen stone ruins.  A small dirt "+
	"path, quite narrow and not easily discernable, curves here "+
	"from north to southwest.  Along its edges lie fallen stones, "+
	"though they are of little interest to you, and look too heavy "+
	"to pick up, anyway.\n");
    
    AE(RHUN+"ruins/sw_side", "north");
    AE(RHUN+"ruins/hag_rm", "southwest");
    
    add_item(({"stone", "stones", "ruins"}), "The stones which stand "+
	"at the edges of this path are the fallen remains of what was "+
	"perhaps once a great building or shrine of some sort.  They "+
	"appear quite heavy, and are of no real interest.\n");
}
