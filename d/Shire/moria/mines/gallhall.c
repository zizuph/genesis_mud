#include "defs.h"

CONSTRUCT_ROOM
{
    add_prop(ROOM_I_NO_TELEPORT,"That is not possible here.\n");
    set_short("Gallery of a huge hall");
    set_long(
	"You are on a ledge, or a gallery overlooking a huge hall.\n"+
	"It is dim below, though you estimate the size of the hall "+
	"to be a hundred yards long and as equally high. On the outside "+
	"there is a path without railings which winds down into the hall. "+
	"Be careful! Watch your steps, and avoid meetings trolls down there. "+
	"There is an opening in the northern wall, and the gallery continues "+
	"east and south a short distance.\n");
    add_item("hall",
	"You are unable to figure other details due to the lack of light.");
    add_item(({"ledge","gallery"}),
	"The gallery itself must once have been a nice architectural feature "+
	"of the Mines of Moria, but it has fallen in decay now.");
    add_item("path",
	"It looks dangerous enough, but you might go down with a little caution.");
    add_item(({"opening","wall"}),
	"There is an opening in the northern wall into what seems to be a corridor.");
    NORTH("corr4");
    EAST("gall_e");
    SOUTH("gall_s");
    DOWN("bighalln");
}
