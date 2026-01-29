#include "defs.h"

inherit STAND_LIB + "rom";

create_rom()
{
    set_short("On the old North Road northwest of Bree");

    set_long(
	"You are walking on the Old North Road west of Bree-Hill. "+
	"The road leads south to the crossing of the Great East Road "+
	"and the Greenway. In the southeast you see the town of Bree "+
	"and in that direction a small road leads into a small opening in "+
	"a hedge on the other side of a dike. This dike and hedge "+
	"must serve as an attempt to protect the village with physical "+
	"obstructions.\n");

    add_item(({"hill","bree-hill"}),
	"You see the steep slopes of Bree-hill on this side, and in "+
	"the south-east you can see a lane winding towards some holes.\n");
    add_item(({"holes","lane"}),
	"Well, as it is quite far, you see nothing special of interest.\n");
    add_item(({"road","greenway"}),
	"This is the continuation of the Greenway to the north, and you "+
	"can understand why it is called so, because grass grows on it.\n");
    add_item("grass",
	"Well, surely since grass grows here, it cannot be used so much.\n");
    add_item(({"gates","dike","hedge"}),
        "There is only one way to get past the hedge, and that is through "+
	"the gate, but it seems that the North Gate is securely closed "+
	"and barred from the inside.\n");

    add_exit("/d/Gondor/arnor/greenway/nr1", "north", 0);
    add_exit(STAND_DIR + "cross", "south", 0);
    add_exit(STAND_DIR + "ngate", "southeast", "@@no_enter");
}

int
no_enter()
{
    write("You cannot enter the small opening, because it is blocked with "+
	  "sturdy gates.\n");
    return 1;
}
