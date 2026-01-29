
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Corner in stone hallway");
    set_long("You walk through the stone hallways of this ruined "+
	"castle.  The corridor makes a turn here, heading from "+
	"north to west.\n");

    add_item(({"hall", "hallway", "corridor", "wall", "walls"}), 
	"The walls of this castle are made from blocks of grey "+
	"stone.  It has begun to crumble in places, though it "+
	"appears to still be quite safe.  The passage turns here "+
	"from north to west.\n");
	
    AE(RHUN+"castle/hall_e","north");
    AE(RHUN+"castle/cross", "west");

    IN;
}
