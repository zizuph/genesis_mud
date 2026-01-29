/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("An old deserted street");
        set_long(BS(
           "You are in an old ruined street of Xak Tsaroth deep underground in"
	 + " a huge cavern. The buildings"
	 + " are in pretty good shape considering the stresses the cataclysm"
	 + " must have placed on them though many of the walls are leaning"
	 + " dangerously. A small building seems in particulary good shape to"
	 + " the east and an old metal sign hangs over the doorway.", 70));

	add_exit(DDIR + "highstreet1.c", "north", 0);
	add_exit(DDIR + "sage1.c", "east", 0);
	add_exit(DDIR + "vinetop.c", "south", 0);

	add_item(({"sign", "metal sign"}), "@@sign");
	add_item(({"building", "buildings", "small building", "wall", "walls"}), "@@walls");
	add_cmd_item("sign", "read", "The sign reads: 'The Sage Front.'\n");

	INSIDE
        DARK
}

sign()
{
	write("The sign reads: 'The Sage Front.'\n");
	return "";
}

walls()
{
	write(BS("The buildings are mostly still standing but in a dangerous shape"
	 + " many of the walls are leaning over ready to collapse. However"
	 + " one small building to your east looks in a better state than"
	 + " most.", 70));
	return "";
}
