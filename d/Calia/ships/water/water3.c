#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
	set_short("In the middle of the sea");
	set_long("The coastline of Sparkle is fairly close. "+
		"You can see people moving on the dock and boats "+
		"in the harbour.\n");

	add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
