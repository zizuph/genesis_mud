#include "forest.h"

create_forest()
{
    set_short("River bank of Greyflood");
    set_long(
	"You are standing on the river bank of the mighty river Greyflood, "+
	"a spot where you can see that it turns slowly from the northeast "+
	"to the south. You could either follow it or walk into the dense "+
	"forest in the southwest, or west where the forest grows. "+
	"In the northwest a small trail walks in between some large boulders.\n");

    NORTHEAST("dwarfroad.1");
    NORTHWEST("f0103");
    WEST("f0102");
    SOUTHWEST("f0101");
    SOUTH("f0201");
    reset_room();
}

void
reset_room()
{
}
