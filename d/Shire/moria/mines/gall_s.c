#include "defs.h"

CONSTRUCT_ROOM
{
    add_prop(ROOM_I_NO_TELEPORT,"That is not possible here.\n");

    set_short("South end of the Gallery");
    set_long(
	"This is the southern end of the Gallery. It is very dirty here, and "+
	"it seems like it is not a particulary well-visited place. The gallery "+
	"lies east of you, though you can't descend from here since it is about "+
	"hundred yards down to the bottom, but there is a narrow crack in the "+
	"west in which you could squeeze into.\n");
    add_item("hall",
	"You are unable to figure other details due to the lack of light.");
    add_item(({"ledge","gallery"}),
	"The gallery itself must once have been a nice architectual feature "+
	"of the Mines of Moria, but it has fallen in decay now.");
    add_item(({"crack","wall"}),
	"It is a very narrow crack in the western wall, you could squeeze "+
	"yourself into it.");
    NORTH("gallhall");
    WEST("gallcrck");
}
