inherit "/std/room";

#include "/d/Emerald/defs.h"

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	
	set_short("Living room");
	set_long("   This is the living room of the elven house. "+
		"The walls are covered with expensive paintings and "+
		"there is a huge library here. The furniture seems well "+
		"used but is in very good condition. Who would think of "+
		"leaving such a nice place?\n\n");

	add_item(({"painting", "paintings", "walls"}), "The walls are "+
		"covered with paintings that depict different "+
		"landscapes.\n");
	add_item("furniture","The furniture does not seem to have been "+
		"affected by age, and looks very comfortable. You don't "+
		"dare sit on it for fear of making it dirty.\n");
	add_item(({"library", "books"}), "This looks like the library of "+
		"someone like a mayor that would be interested in law and "+
		"government.\n");

	add_exit(VILLAGE_DIR + "diningroom", "north");
	add_exit(VILLAGE_DIR + "foyer", "west");
}
