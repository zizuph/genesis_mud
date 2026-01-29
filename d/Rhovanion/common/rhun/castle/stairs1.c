
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Bottom of staircase");
    set_long("You stand at the bottom of a narrow staircase.  It "+
	"leads up from here to the castle's second level.  There is "+
	"also a stone hallway just to the southeast.\n");

    add_item(({"wall", "walls", "stone", "stones", "grey stone"}), 
	"The walls here are made of a light-grey stone.  They have "+
	"begun to crumble in places, due to natural entropy and the "+
	"passage of time.\n");
    add_item(({"stairs", "stairway", "staircase", "stair"}), 
	"The stairs are narrow, made of light-colored stone like "+
	"the rest of this castle,  and head upward from here.\n");
    add_item(({"hall", "hallway", "southeast"}), "A hallway "+
	"stands just southeast of this point.\n");
	
    AE(RHUN+"castle/hall_w","southeast");
    AE(RHUN+"castle/2stairs","up");

    IN;
}

