inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("High Road");
	set_long(BSS("You are at the north end of High Road, close to the "+
		"city walls. You can see many houses to your west and "+
		"southwest. You see a house just to the east, and "+
		"behind it you see a small castle, built close to the "+
		"city wall.\n"));

	add_exit(HGH_STR+"road4","southeast",0);
	add_exit(NOBL_D+"house1","east","@@closed");

}

closed()	{
	write(BSS("A little gnome pops out in the door telling you "+
		"to get out of here, since his master doesn't want "+
		"guests today.\n"));
	return 1;
}

