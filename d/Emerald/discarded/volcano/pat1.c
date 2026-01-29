// Room one of pth to native camp.... Pat1.c
// Purpose: To lead from volcano to woods and camp
//	To add animal npcs and possibly to lead into deeper woods.
// Creator: Triana
// Date: March 11 1997
inherit "/std/room";
#include "/d/Emerald/defs.h"

create_room()
{
	set_short("Forest Path");
	set_long("You descend from the volcano to a tight forest path " +
	"by looking at the path, you conclude that the people who " +
	"cleared it wanted to leave as many trees living as possible. " +
	"The volcano stands behind you, and the path leads further " +
	"into the forest.\n");

	add_exit("v27.c", "up", 0,3);
	add_exit("pat2.c", "east");
}
