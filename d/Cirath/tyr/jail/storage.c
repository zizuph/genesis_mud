/* Storage room on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
	set_short("storage");
	set_long("This is a miscellaneous storage room. In here one can "
		+"almost find anything. You can see everything from tools "
		+"to old barrels and pots. Shelves stands against all four "
		+"walls. There is a couple chests piled up in the center of "
		+"the room. Heaps of various junk is spread across the room. "
		+"There are even some piles of old tapestrys.\n");

	add_item("shelves", "There are alot of shelves in this room. The "
		+"shelves is filled with all kind of strange things.\n");

	add_item("chests", "A couple of chests are piled up on the floor. "
		+"There are both small metal boxes and heavy, big, crude, "
		+"wooden chests.\n");

	add_item(({"heaps", "junk"}), "They are full of various junk.\n");
	
	add_item("junk", "The junk is put into neat little heaps.\n");

	add_item("tapestrys", "They look pretty old and dusty. They must have "
		+"been in here for a very long time.\n");

	INSIDE

	add_exit(TYR_JAIL + "weproom.c", "northwest", 0,1);
	add_exit(TYR_JAIL + "armroom.c", "northeast", 0,1);
}
