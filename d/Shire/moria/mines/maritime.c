#include "defs.h"

object cylinder;

CONSTRUCT_ROOM
{
    set_short("Maritime room");
    set_long(
	"This is the Maritime room. The walls are adorned with anchors and "+
	"cordage, and paintings of the sea decorates the ceiling. There is "+
	"an opening to the north here, and also one in the south.\n");
    add_item("floor", "It is wooden, and by the looks and the smell of the "+
	"sea from it, you'd bet it was once taken from an old ship.");
    add_item(({"ceiling", "paintings"}),
	"You see that they depict the oceans in all colours of green to blue.");
    add_item(({"walls","wall","anchors","cordage","ropes"}),
	"The walls are adorned with anchors and cordage, but the anchors are "+
	"too heavy to be carried, and the ropes seems too heavy to have any "+
	"use for you. Though they match perfectly the aura of this room.");
    NORTH("smhollow");
    SOUTH("narrpass");
    reset();
}

/*
RESET_ROOM
{
    if (!cylinder || !present(cylinder, TO)) {
	cylinder = clone_object(MORIA_OBJ+"cylinder");
	cylinder -> move(TO);
    }
}
 
*/
