/* Library on first floor in Jail of Tyr... /*
/* Zayn March 97 */

inherit "/std/room";
#include "defs.h"

void
create_room()
{
	set_short("library");
	set_long("This room is well lit and well organized. Shelves stand "
		+"in rows. This is the prison library. Here they store "
		+"different information about prisoners and history of "
		+"the jail. The room is kept clean and free from sand and "
		+"dust. A desk is standing in the center of the room.\n");

	add_item("shelves", "There are many shelves, containing informations "
		+"about slaves, prisoners, guards and history of the jail. "
		+"The books in the shelves looks well kept and in order.\n");

	add_item("books", "They stands in shelves organized in alphabetical "
		+"order, or sorted by date.\n");

	add_item("desk", "This is a reading desk, on which you can read "
		+"books and write down information in books or parchment "
		+"scrolls.\n");

	INSIDE;

	add_exit(TYR_JAIL + "corner2.c", "north", 0,1);
	add_exit(TYR_JAIL + "jail1_3.c", "south", 0,1);
}
