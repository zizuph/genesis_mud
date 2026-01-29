#include "defs.h"

CONSTRUCT_ROOM
{
    add_prop(ROOM_I_NO_TELEPORT,"That is not possible here.\n");

    set_short("Southern end of Big Hall");
    set_long(
	"You are standing by the southern end of the Big Hall. It is a great "+
	"hall, and the ceiling looms high above you. There is also an arched "+
	"portal in the south wall leading into an archway.\n");
    add_item("hall",
	"The hall is quite big, therefore it's name. It extends west and south "+
	"and the ceiling looms a hundred yards above you.");
    add_item("ceiling",
	"Looking upwards, you can see the sad remains of the once beautiful "+
	"artistry of the dwarves. Now, however, the paintings are covered with soot and "+
	"you can just imagine how it looked like when the Halls were bright "+
	"and the area was inhabited.");
    add_item("painting",
	"You see colours vaguely, but you can not figure out what it is in this "+
	"darkness and the sotting of the painting.");
    add_item("floor",
	"The floor seems unornamented, though it feels exceptionally smooth, "+
	"and is a sign of the great craftmanships of the dwarves that once "+
	"lived and made the Mines.");
    add_item(({"portal", "archway"}),
	"The archway is to the south through an arched portal. The portal itself "+
	"is decorated with intricate patterns.");
    add_item("patterns",
	"The patterns criss-cross and looks like intervening dragons.");
    NORTH("bighalln");
    SOUTH("archway");
}
