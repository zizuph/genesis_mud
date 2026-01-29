#include "../../ctower.h"

inherit AIRSTD;

#include <macros.h>

void
create_air()
{
    add_item(({"stair", "stairs", "stairway"}),  "This "+
	"stairway appears to be quite sturdy even though "+
	"there doesn't seem to be any visible support.\n" );
   
    add_exit(CTOWER_ROOM_ELEM + "earth9", "north");
    add_exit(CTOWER_ROOM_ELEM + "air10", "northwest");
    add_exit(CTOWER_ROOM_ELEM + "air11", "northeast");
    add_exit(CTOWER_ROOM_FIN + "finalsd", "up");
}
