#pragma save_binary

#include <stdproperties.h>
#include "default.h"

create_room() 
{
	set_short("Stairs in the cloud");
	set_long(
		"You stand on a golden staircase\n" +
		"it has no handholds so it feels a little bit frigthening!\n" +
		"Your are inside a cloud so you cant see a thing!\n" +
		"You are thorougly soaked in water from the cloud.\n"
	);
	add_exit(THIS_DIR + "stairtop", "up", "@@msg");
	add_exit(THIS_DIR + "stairlow", "down", "@@msg");
	change_prop(ROOM_I_LIGHT, 10);
}

msg()
{
	write("You are walking and walking on the golden stairs.\n");
	return 0;
}