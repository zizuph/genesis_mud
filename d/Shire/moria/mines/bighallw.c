#include "defs.h"

CONSTRUCT_ROOM
{
    add_prop(ROOM_I_NO_TELEPORT,"That is not possible here.\n");

    set_short("West end of the Big Hall");
    set_long(
	"You are standing at the west end of the Big Hall.\n"+
	"The floor is of smooth rock and it contains no ornaments. "+
	"The Hall extends to the east and there is a passage leading "+
	"south into a smaller room.\n");
    add_item("hall",
	"The hall is quite big, therefore it's name. It extends west and south "+
	"and the ceiling looms a hundred yards above you.");
    add_item("ceiling",
	"Looking upwards, you can see the sad remains of the once beautiful "+
	"artistery of the dwarves. Now, however, the paintings are sotted and "+
	"you can just imagine how it looked like when the Halls were bright "+
	"and the area was inhabited.");
    add_item("painting",
	"You see colours vaguely, but you can not figure out what it is in this "+
	"darkness and the sotting of the painting.");
    add_item("floor",
	"The floor seems unornamented, though it feels exceptionally smooth, "+
	"and is a sign of the great craftmanships of the dwarves that once "+
	"lived and made the Mines.");
    add_item(({"passage", "south exit", "smaller room"}),
	"Looking south, there is a passage leading to a smaller room. It " +
	"looks dark in there, but you couldn't know for sure, perhaps " +
	"go there?\n");
    EAST("bighalln");
    SOUTH("secret");
}
