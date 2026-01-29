#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
	set_short("Terel on the horizon");
	set_long("You can make out Terel on the horizon.\n");

	add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
