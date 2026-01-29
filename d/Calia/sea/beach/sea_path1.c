
/*	coder(s):		coded by Amelia 5/95
*
*       Minor alterations by Maniac 18/8/96
*/

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
	set_short("A sandy path");
	set_long("This is a small path leading toward sand dunes.  "+
		"As you near the dunes, the path begins to rise slightly. "+
		"Your feet sink in the sand, and it's a little "+
		"harder to walk here.  On the dunes there is pampas "+
		"grass which sways gracefully in the breeze from the sea, "+
		"which must be just over the rise. East of here "+
		"you see a cobbled road that leads to the moorland "+
		"in the south. \n");

	add_item((({"path", "sandy path"})),
		("The path leads from a cobbled road in the "+
		"east to a row of dunes to the west, where it is much "+
		"steeper.  It's covered in white sand, which "+
		"makes walking a little more difficult.\n"));
	add_item((({"dune", "dunes"})),
		("The dunes to your west are hills of white sand.\n"));
	add_item((({"sand", "white sand"})),
		("The sand is as white as sugar. It makes walking "+
		"a little difficult.\n"));
	add_item((({"grass", "pampas grass"})),
		("Pampas grass grows in clumps here and there "+
		"in the sand.  Its tall, narrow fronds sway gracefully "+
		"when they catch a breeze.  As you examine the grass, "+
		"you see that it has stalks topped with white, "+
		"feathery tassels.\n"));

	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE, 0);
	add_prop(ROOM_I_IS, 1);

	add_exit(ROAD+"road18", "east", 0,0);
	add_exit(BEACH+"sea_path2", "west", 0,3);
}
