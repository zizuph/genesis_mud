#pragma save_binary

#include <stdproperties.h>
#include "default.h"

create_room() 
{
	set_short("Stairs in the air");
	set_long(
		"You stand on a golden staircase\n" +
		"it has no handholds so it feels a little bit frigthening!\n" +
		"The stairs continue endlessly below you through the clouds,	\n" +
		"the stairs seems to lead into the underside of a gigantic rock.\n"
	);
	add_exit(THIS_DIR + "green", "up", "@@up_msg");
	add_exit(THIS_DIR + "stairmid", "down", "@@down_msg");
	change_prop(ROOM_I_LIGHT, 10);
}

down_msg()
{
	write("You are walking and walking on the golden stairs.\n");
	return 0;
}

up_msg()
{
	write("You walk up endless stairs without end.\n" +
		"You come out on a green grass lawn.\n" +
		"You must be on an island floating in midair!\n" 
	);
	return 0;
}