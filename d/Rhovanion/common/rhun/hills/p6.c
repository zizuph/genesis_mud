
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Mountain path");
    set_long("A narrow mountain path approaches the "+
	"front of a large, run-down castle of light grey "+
	"stones here.  The castle is just to the north, "+
	"standing wedged in amongst the mountain peaks.  "+
	"The path winds its way back to the south from "+
	"here.\n");
	
    AE(RHUN+"castle/entry", "north");
    AE(RHUN+"hills/p5", "south");
    
    add_item("castle", "The castle is not very large.  It "+
	"stands waiting just to the north.  You can see "+
	"that it is quite run-down, ruined and crumbled in "+
	"places.\n");
    add_item("path", "The path approaches a ruined stone "+
	"castle to the north, and heads back off to the south "+
	"as well.\n");
}
