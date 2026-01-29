#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
	set_short("In the middle of the sea");
	set_long("The harbour of Shire is very close. "+
		"To the south you see an expanse of open sea.\n");

	add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
