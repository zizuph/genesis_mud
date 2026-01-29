
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Top of staircase");
    set_long("You stand at the top of a secret staircase.  It "+
	"leads down from here to what appears to be a cavernous "+
	"basement.  Back to the west is a small, square room.\n");

    add_item(({"stairs", "stairway", "staircase", "stair"}), 
	"The stairs are narrow, made of light-colored stone like "+
	"the rest of this castle,  and head downward from here.\n");
	
    AE(RHUN+"castle/secretroom","west");
    AE(RHUN+"castle/basement","down");

    IN;
}

