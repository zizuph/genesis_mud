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
	 + " the west.", 70));

	add_exit(DDIR + "highstreet2.c", "south", 0);
	add_exit(DDIR + "flourroom.c", "west", 0);

	add_item(({"building", "buildings", "small building", "wall", "walls"}), "@@walls");

	INSIDE
        DARK
}

walls()
{
	write(BS("The buildings are mostly still standing but in a dangerous shape"
	 + " many of the walls are leaning over ready to collapse. However"
	 + " one small building to your west looks in a better state than"
	 + " most.", 70));
	return "";
}
