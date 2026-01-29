
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_castle_guard_hall_e"))
    {
        object guard;
	guard=clone_object(RHUN+"npc/castle_guard");
        guard->set_living_name("_castle_guard_hall_e");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Stone passage");
    set_long("You walk through the stone passages of this ruined "+
	"castle.  The corridor splits here, branching off to the "+
	"northwest and south, while a small room stands just "+
	"northeast of here.\n");

    add_item(({"hall", "hallway", "corridor", "passage", "passages",
	"passageway", "passageways"}), "The hall is made from blocks "+
	"of light grey stone, and heads from northwest to south.\n");
    add_item(({"northeast", "chamber", "room"}), 
	"A very small chamber stands "+
	"just northeast of here.  You may enter by heading in that "+
	"direction.\n");
    add_item(({"stone", "stones", "wall", "walls", "bricks"}), 
	"The walls of this ruined castle are made of bricks of "+
	"a light-grey stone.  They have begun to crumble in places, "+
	"though it is still plenty safe here.\n");

    AE(RHUN+"castle/hall_se","south");
    AE(RHUN+"castle/hall_n", "northwest");
    AE(RHUN+"castle/secretroom", "northeast");

    IN;

    reset_room();

}

