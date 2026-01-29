/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("An old deserted shop");
        set_long(BS(
           "You find yourself in a ruined shop. Looking around you'd guess"
	 + " that this used to be an alchemists of some sort. Glass apparatus"
	 + " and bottles line the walls but all are long since broken or smashed"
	 + " beyond use. A small doorway leads into a storeroom to the south.", 70));

	add_exit(DDIR + "highstreet2.c", "west", 0);
	add_exit(DDIR + "sage2.c", "south", 0);

	INSIDE
        DARK
}

