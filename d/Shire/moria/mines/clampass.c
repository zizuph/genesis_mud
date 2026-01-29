#include "defs.h"

object rat;

CONSTRUCT_ROOM
{
    set_short("Clammy passage");
    set_long(
	"You are in the Clammy Passage. A smell of putrification ascends "+
	"the room, and there is mud on the floor. The passage continues "+
	"north and south, while there is an opening in the east.\n");
    add_item(({"smell", "putrification", "air"}),
	"A disgusting smell of putrification and decay permeates the air.");
    add_item(({"mud","floor"}),
	"The floor is muddy and bad-smelling.");
    add_item(({"walls","wall", "ceiling"}),
	"The walls and the ceiling are covered in mud.");
    add_item("passage", "Leading north and south it is covered with smelling "+
	"mud.");
    add_item("opening", "To the east, you can see a room that is partitioned off.");
 
    add_prop(ROOM_I_HIDE, -1);
    NORTH("dirthole");
    SOUTH("depress");
    EAST("partoff");
    reset();
}

RESET_ROOM
{
    if (!rat || !present(rat))
	{
	    rat = clone_object(MORIA_NPC + "rat");
	    rat -> move(TO);
	}
}


