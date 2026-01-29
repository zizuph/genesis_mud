#pragma save_binary

#include "default.h"
#include </secure/std.h>
#include <stdproperties.h>

create_room() 
{
	set_short("Wizard lounge");
	set_long(
		"Wizard lounge.\n" +
		"This is a room for socializing and discussion.\n" +
		"To the north is the entrance hall,\n" +
		"below is the war room,\n" +
		"to the west is your workroom,\n" +
		"to the south is the discussion and planning board,\n"  +
		"and to the east is the idea board.\n" 
	);	
	add_exit(THIS_DIR + "entrance", "north");
	add_exit(THIS_DIR + "flame", "down");
	add_exit("@@move_home", "west"); /* this is changed in init() */
	add_exit(THIS_DIR + "discuss", "south");
	add_exit(THIS_DIR + "idea", "east");
	change_prop(ROOM_I_LIGHT, 10);
}

move_home()
{
	string	name;
	string	homedir;
	name = this_player()->query_real_name();

	homedir = SECURITY->wiz_home(name);
	return homedir;
}