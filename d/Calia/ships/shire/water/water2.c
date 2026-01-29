#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
	set_short("In the middle of the sea");
	set_long("You can just see the harbour of Gelan on the "+
		"horizon. Sea gulls and pelicans fish in the "+
		"sea, and occasionally a dolphin leaps "+
		"in the water.\n");

	add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
