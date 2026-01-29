/* Armour storage room on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
	set_short("storage");
	set_long("A big desk stands along the northern wall. On opposit "
		+"sides of the desk stands shelves. The other walls are "
		+"covered with armour racks. Guards stand on both sides of "
		+"the room to guard the armours. A great wheel hangs from "
		+"the ceiling.\n");

	add_item(({"big desk", "desk"}), "The desk is used to mend armours. "
		+"There are some armours on the desk right now, waiting to "
		+"be taken care of.\n");

	add_item("racks", "The racks are nearly filled with armours of all "
		+"kinds. You could equip a whole army with all these "
		+"armours.\n");

	add_item("wheel", "The wheel is about six feet in diameter and it "
		+"hangs about 12 feet above the floor. It has exactly ten "
		+"spokes, made of wood. The wheel is fastened to the "
		+"ceiling with a long metallic pole.\n");

	add_item("spokes", "They are made of wood and is fastened in an "
		+"orderly fashion on the wheel.\n");

	add_item("pole", "It looks like it was made of some sort of metal. "
		+"It connects the wheel with the ceiling.\n");

	add_item("ceiling", "A great wheel hangs from the ceiling, connected "
		+"with a metallic pole.\n");

	add_item("guards", "They look at you with grim expressions. Their "
		+"eyes are fixed on you. They will not let you get close "
		+"to the armours without permission.\n");

	add_cmd_item("armours", ({"take", "get", "pick"}), "The guards give "
		+"you a grim look which makes you hesitate. You regrets your "
		+"action and leaves the weapons where they are.\n");

	INSIDE

	add_exit(TYR_JAIL + "jail1_3.c", "east", 0,1);
	add_exit(TYR_JAIL + "weproom.c", "west", 0,1);
	add_exit(TYR_JAIL + "storage.c", "southwest", 0,1);
}
