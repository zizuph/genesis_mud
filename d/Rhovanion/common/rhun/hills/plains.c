
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("On the plains.");
    set_long("You are on the plains of Rhun.  A road lies "+
	"back to the west, and a riverbank is just east of "+
	"here.\n");
	
    AE(RHUN+"roads/section5/c", "west");
    AE(RHUN+"hills/r1", "east");
    
}
