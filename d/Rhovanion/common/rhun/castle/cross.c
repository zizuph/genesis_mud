
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_castle_guard_cross"))
    {
        object guard;
	guard=clone_object(RHUN+"npc/castle_guard");
        guard->set_living_name("_castle_guard_cross");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Hallway crossing");
    set_long("A wide hallway crosses this point, heading from "+
	"east to west.  There is also a doorway of grey stone "+
	"heading south into a large entryway, while an even "+
	"greater chamber is to the north.\n");

    add_item(({"hall", "hallway"}), "The hall is made from blocks "+
	"of light grey stone, and heads from east to west.\n");
    add_item(({"north", "chamber"}), "A very large chamber stands "+
	"just north of here.  You may enter by heading in that "+
	"direction.\n");
    add_item(({"south", "entryway", "doorway"}), "A stone doorway "+
	"leads south into this ruined castle's large entryway.\n");
    add_item(({"stone", "stones", "wall", "walls", "bricks"}), 
	"The walls of this ruined castle are made of bricks of "+
	"a light-grey stone.  They have begun to crumble in places, "+
	"though it is still plenty safe here.\n");

    AE(RHUN+"castle/entryway","south");
    AE(RHUN+"castle/throneroom","north");
    AE(RHUN+"castle/hall_sw", "west");
    AE(RHUN+"castle/hall_se", "east");

    IN;

    reset_room();

}

