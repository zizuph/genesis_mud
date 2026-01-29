inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

init()
{
	::init();
	add_action("do_start", "start");
}

create_room()
{
	set_short("Quarters.\n");
	set_long("This room is filled with sleeping bunks. Here members can rest"
		+" when they aren't out spreading the fear of Melkor in Genesis. If"
		+" you wish to start here, you can.\n");
	
	add_item(({"bunks", "bunk" }), "They look quite comfortable, and all of"
		+" them are neatly made up.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	
	add_exit(CULT_DIR + "t_med", "southwest", 0);
}

int
do_start(string str)
{
	NF("Start where?\n");
	if (str != "here") return 0;

	TP->set_default_start_location(CULT_DIR + "startroom");
	write("You will now start your journeys from the guildhome.\n");
	return 1;	
}	