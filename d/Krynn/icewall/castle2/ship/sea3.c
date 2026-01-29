inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("In Unknown Waters");
    set_long("You are in seldomly passed waters. Somewhere to the far east, " +
	"plains of Tarsis stretch their dry surface.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
