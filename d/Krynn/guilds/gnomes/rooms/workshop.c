/* Created by Dajala
 * The room where members of the guild can get the kit for the modules
 */

inherit "/d/Krynn/std/room";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../guild.h"
#include "../modules.h"

#define PARENT  "/d/Krynn/"
#define TDIR    PARENT + "gnome/"
#define MON	    TDIR + "monster/"

object ob;

void
create_room()
{
	LIGHT;
	INSIDE;

	set_short("The workshop");
	set_long("This part of the cave is rather small compared to "
		+ "the central cavern. A huge, impressive counter "
		+ "occupying the rear part catches your attention.\n"
		+ "The cave continues to the north and there is a small "
		+ "room to the west.\n");

	add_item("counter", "It's made from stone. There is a poster "
		+ "nailed to the front.\n");
	add_item("poster", "You can read it.\n");
	add_cmd_item("poster", "read", 
		"Currently available are the following modules:\n\n@@modules");

	seteuid(getuid(TO));
	set_alarm(1.0, -1.0, "reset_room");

	add_exit(ROOMS + "joinroom", "east", 0);
	add_exit(ROOMS + "taproom", "north", 0);
	add_exit(ROOMS + "deposit", "west", 0);
}

void
reset_room()
{
	if(!ob) 
	{
		ob = clone_object(MON + "kit_gnome");
		ob->move_living("xxx", TO);
	}
}

string
modules()
{
	string str = "";
	int i;

	for(i=0;i<sizeof(TYPES);i++)
		str = str + " - The " + capitalize(TYPES[i]) + "\n";
	str += "\nYou might want to check 'help gnomes <modules>' for more "
		+ "information about a specific one.\n";
	return str;
}
