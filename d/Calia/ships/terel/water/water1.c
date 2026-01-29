#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
	set_short("In the middle of the sea");
	set_long("The busy port of Gelan is quite close, and "+
		"you can see people moving about on the dock "+
		"and small boats in the harbour.\n");

	add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}