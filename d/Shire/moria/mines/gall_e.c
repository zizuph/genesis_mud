#include "defs.h"

CONSTRUCT_ROOM
{
    add_prop(ROOM_I_NO_TELEPORT,"That is not possible here.\n");

    set_short("East end of gallery");
    set_long(
	"You are on the eastern end of a gallery overlooking a huge hall. "+
	"It is rather clean here, in contrast with the rest of the Mines "+
	"which are dirty and unkept.");
    add_item("hall",
	"You are unable to figure other details due to the lack of light.");
    add_item(({"ledge","gallery"}),
	"The gallery itself must once have been a nice architectural feature "+
	"of the Mines of Moria, but it has fallen in decay now. This place "+
	"is remarkibly clean, and you wonder why.");
    WEST("gallhall");
}
