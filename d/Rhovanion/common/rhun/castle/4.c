
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_castle_guard_4"))
    {
        object guard;
	guard=clone_object(RHUN+"npc/castle_guard");
        guard->set_living_name("_castle_guard_4");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Tower room");
    set_long("You have reached the tower room at the top of this "+
	"ruined castle.  It is perfectly round, with a wooden floor "+
	"and walls of blocks of light-grey stone.  But there is nothing "+
	"here: this room has been totally emptied of whatever "+
	"was once kept here.  The only exit is back down the "+
	"stairs.\n");

    add_item(({"wall", "walls", "stone", "stones", "grey stone"}), 
	"The walls here are made of a light-grey stone.  They have "+
	"begun to crumble in places, due to natural entropy and the "+
	"passage of time.\n");
    add_item(({"stairs", "stairway", "staircase", "stair"}), 
	"The stairs are narrow, made of light-colored stone like "+
	"the rest of this castle,  and head down from "+
	"here.\n");
    add_item(({"floor", "wooden floor"}), "The floor of this "+
	"tower room is made of a dark-colored wood, probably a "+
	"species from the forests of northeastern Rhun.  The stairs "+
	"head downward through a hole in the center of the "+
	"room.\n");
		
    AE(RHUN+"castle/3stairs", "down");

    IN;

    reset_room();
    
}
