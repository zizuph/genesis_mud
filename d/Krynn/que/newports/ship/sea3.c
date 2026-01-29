inherit "/std/room";
#include <stdproperties.h>

create_room()
{
    set_short("In Unknown Waters");
    set_long("You are in unknown waters. Wherever you look you only see water,\n" +
	"blue sea water.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
