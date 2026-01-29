/* house8.c: Manor entry. Zayn 02-16-97 */

#pragma strict_types

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("noble", ATH_PERSON+"rich_hmn.c", 1, 1);
    bring_room_mob("slave", ATH_PERSON+"slav_hmn.c", 2);
}

void
create_room()
{
	set_short("entry hall of the manor");
	set_long("This is fabulous room in a Manor. Everything looks very "
		+"orderly, and you can't find any sand, dust or other things that "
		+"show this is a home in use. The walls are decorated "
		+"with many paintings and portraits. The furniture in this "
		+"home is of a very fine quality, not at all like what you can "
		+"find in other homes in this city. By the condition of the shelves you can "
		+"imagine the owner's personal passion for order. There is "
		+"also a high-quality tapestry on one of the walls.\n");

	add_item(({"sand", "dust"}), "Even though you search you can't find "
		+"anything that you could call sand or dust.\n");

	add_item(({"wall", "walls"}), "You can see many different paintings, "
		+"portraits, and shelves on the walls: Everything arranged "
		+"in a strict order. Every painting and portrait hangs exactly "
		+"as high as all the others. There is also a tapestry on one "
		+"of the walls.\n");

	add_item(({"paintings", "painting", "portraits", "portrait"}), "All "
		+"the paintings and portraits hang equally high and "
		+"they are placed in a strategic order, making it easier to "
		+"keep the place clean and in an orderly fashion.\n");

	add_item("furniture", "The quality of the furniture is remarkable "
		+"high. You can't stop wondering where this kind of furniture "
		+"comes from.\n");

	add_item(({"shelves", "shelf"}), "The books in the shelves are all in "
		+"alphabetical order. There are many books here and some of "
		+"them look rather interesting, but they are all marked with "
		+"the symbol of this house and not worth stealing.\n");

	add_item("tapestry", "This tapestry appears to be a historical "
		+"picture of a journey through a dry and abandoned desert. "
		+"It looks like it is worth a lot of money, if you can sell "
		+"it that is.\n");

	add_cmd_item("tapestry", ({"get", "take", "pick", "pull", "steal"}),
		 "No, it is not worth the effort. What if you get caught "
		+"trying to sell it? Wow that would be a hard punishment. "
		+"You decide that it is better to leave it where it is.\n");

	INSIDE

	add_exit(TZ_NOBLE+"", "north", 0, 1);
	add_exit(TZ_NOBLE+"house8b.c", "east", "@@walk_outside", 1);
	add_exit(TZ_NOBLE+"house8a.c", "west", 0, 1);
	reset_room();
}

public int
walk_outside()
{
    TP->catch_msg("You feel the heat as you walk outside.\n");
    return 0;
}
