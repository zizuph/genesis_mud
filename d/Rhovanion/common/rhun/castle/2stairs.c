
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    reset_euid();

    if(!find_living("_castle_guard_2stairs"))
    {
        object guard;
	guard=clone_object(RHUN+"npc/castle_guard");
        guard->set_living_name("_castle_guard_2stairs");
        guard->move(TO);
    }
}

create_room()
{
    set_short("Staircase");
    set_long("You stand on the second level of this stone castle.  "+
	"A wide hallway heads east to west here, while stairs lead "+
	"both up and down.  In the distance, you hear the crack of "+
	"thunder.  A few tattered tapestries hang hearby; but they "+
	"have been ruined by the passage of time and the effects of "+
	"natural entropy, for the most part.\n"); 

    add_item(({"wall", "walls", "stone", "stones", "grey stone"}), 
	"The walls here are made of a light-grey stone.  They have "+
	"begun to crumble in places, due to natural entropy and the "+
	"passage of time.\n");
    add_item(({"stairs", "stairway", "staircase", "stair"}), 
	"The stairs are narrow, made of light-colored stone like "+
	"the rest of this castle,  and head both up and down from "+
	"here.\n");
    add_item(({"hall", "hallway"}), "The hallway is quite wide, with "+
	"room for several people to walk abreast.  It leads here from "+
	"east to west.\n");
	
    AE(RHUN+"castle/2east","east");
    AE(RHUN+"castle/3stairs","up");
    AE(RHUN+"castle/stairs1", "down");
    AE(RHUN+"castle/2west", "west");

    IN;

    reset_room();
    
}
