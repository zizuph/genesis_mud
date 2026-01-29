
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_castle_guard_hall_n"))
    {
        object guard;
	guard=clone_object(RHUN+"npc/castle_guard");
        guard->set_living_name("_castle_guard_hall_n");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Curving stone corridor");
    set_long("The stone corridor curves here, heading from southeast "+
	"to southwest.  A window stands in the north wall; outside, "+
	"a storm is brewing.  There is little else to see, save the "+
	"cold and uninviting peaks of the surrounding mountains.\n");

    add_item(({"hall", "hallway", "corridor", "passage", "passages",
	"passageway", "passageways"}), "The hall is made from blocks "+
	"of light grey stone, and heads from southeast to southwest.\n");
    add_item(({"stone", "stones", "wall", "walls", "bricks"}), 
	"The walls of this ruined castle are made of bricks of "+
	"a light-grey stone.  They have begun to crumble in places, "+
	"though it is still plenty safe here.\n");
    add_item(({"view", "window", "out window", "outside", "north"}), 
	"The window is just an empty space in the grey stones of this "+
	"ruined, run-down castle.  Outside, you can see a storm brewing "+
	"among the peaks of the surrounding mountains.\n");

    AE(RHUN+"castle/hall_e", "southeast");
    AE(RHUN+"castle/hall_w", "southwest");

    IN;

    reset_room();

}

