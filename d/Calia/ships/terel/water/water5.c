#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
	set_short("Near Terel");
	set_long("You are now pretty close to the piers of Terel.\n");

	add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
