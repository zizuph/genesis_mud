/* Corner room 2 on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
	bring_room_mob("slave", TYR_NPC+"jailslav.c", 4);
}

void
create_room()
{
	set_short("slave room");
	set_long("Beds are lined up against the walls. Tables and chairs "
		+"stand against the east wall. There are even a window in "
		+"the north wall, giving a view of the outside. A couple "
		+"slaves walks around on the floor. The room is lit by a "
		+"couple of torches.\n");

	add_item("beds", "The beds are very simple, standing two in height. "
		+"It would not be very comfortable to sleep in them.\n");

	add_item("walls", "The walls are bare and full of cracks. They are "
		+"old and have seen better days.\n");

	add_item("tables", "The tables are barely holding together. It "
		+"seems like they could break any minute.\n");

	add_item("chairs", "They are made of wood and it is doubtfull if "
		+"they will hold togheter if you sit on them.\n");

	add_item("window", "Through the window you can see a brick wall. "
		+"The wall is about 3 feet away from the window, which makes "
		+"it very hard to see anything else.\n");

	add_item("slaves", "They walk up and down in the room, looking like "
		+"they were waiting for something.\n");

	add_item("floor", "The condition of the floor isn't the very best. "
		+"there are piles of sand and dust all over the floor.\n");

	add_cmd_item(({"torches", "torch"}), "pull", "As you reach for the "
		+"torch in an attempt to pull it, a slave walks up to you "
		+"and tells you to leave their torches alone.\n");

	TORCHES;
	INSIDE;

	add_exit(TYR_JAIL + "jail1_6.c", "west", 0,1);
	add_exit(TYR_JAIL + "library.c", "south", 0,1);
	add_exit(TYR_JAIL + "jail1_5.c", "southwest", 0,1);
        reset_room();
}
