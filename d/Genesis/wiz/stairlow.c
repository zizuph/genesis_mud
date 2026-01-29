#pragma save_binary

#include <stdproperties.h>
#include "default.h"

create_room() 
{
	set_short("Stairs in the air");
	set_long(
		"You stand on a golden staircase\n" +
		"it has no handholds so it feels a little bit frightening!\n" +
		"Above you the stairs vanish in a cloud.\n" +
		"Below you the stairs delves into the crater of a huge\n" +
		"volcano on an island in the sea.\n"
	);
	add_exit(THIS_DIR + "stairmid", "up", "@@up_msg");
	add_exit(THIS_DIR + "volcano_centre", "down", "@@down_msg");
	change_prop(ROOM_I_LIGHT, 10);
}

up_msg()
{
	write("You are walking and walking on the golden stairs.\n");
	write("You follow the stairs into the cloud.\n");
	return 0;
}

down_msg()
{
	write("You are walking and walking on the golden stairs.\n");
	write("The stairs ends inside a volcano!\n");
	return 0;
}
