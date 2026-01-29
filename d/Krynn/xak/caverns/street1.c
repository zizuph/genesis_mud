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
	 + " must have placed on them. One house to the east is in particularly"
	 + " good shape, even though a small stream of water comes from its"
	 + " doorway and flows further south along the street.", 70));

	add_exit(DDIR + "liftbottom.c", "north", 0);
	add_exit(DDIR + "vinebottom.c", "east", 0);
	add_exit(DDIR + "street2.c", "south", 0);

	add_item(({"stream", "water", "doorway", "house"}), "@@stream");

	INSIDE;
        DARK;
}

stream()
{
	write(BS("A small stream of water flows out from the doorway of the"
	 + " house and off into the darkness to the south. Looking up over the"
	 + " house you can see the water comes down the side of the cliff face"
	 + " the house is against. Vines cover the side of the cliff and the water"
	 + " travels in a small cascade down them.", 70));
	return "";
}
