#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("South of Uruks!!");
    set_long(
	"You are in a passage which winds from the west to the north. "+
	"Two large and ugly Uruk trolls stand in the north talking "+
	"to each other. If they see you, you are dead meat!!\n");
    WEST("bottom");
    add_item(({"trolls","uruks","uruk","uruk trolls"}),
	"You wouldn't even dare to look at them! Run away!!");
}
