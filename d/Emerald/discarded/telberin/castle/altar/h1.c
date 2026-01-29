/* h1.c A file temporarily created for under the altar in /d/Emerald/telberin/t3
 * eventually the Telan-ri quest is planned to be in this room, but for now I
 * just want to make it so players can go down after moving the altar.
 * Geraden February 25, 1998
 */


#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit "/std/room";

void
create_room()
{
	set_short("Under the altar");
	set_long("   You are standing at the bottom of a set of stairs "+
		"that lead back up to the temple from under the altar. "+
		"you are certain this room will be very important "+
		"someday, but right now you can't find any exits other "+
		"than back up the way you came.\n");
	add_item("stairs", "They lead up to the temple.\n");

	add_exit("/d/Emerald/telberin/t3", "up", 0, 0);
}