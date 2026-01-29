/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

create_xak_room()
{
        set_short("An old deserted street");
        set_long(BS(
           "You are in an old ruined street of Xak Tsaroth deep in a huge underground"
	 + " cavern. The buildings"
	 + " to the south have collapsed due to a large amount of water"
	 + " wearing the foundations away. The water comes from the cliff face"
	 + " to the south and presumably from the marsh lands above. The river of water is joined by a small stream from"
	 + " the north and together it flows further west.", 70));

	add_exit(DDIR + "street1.c", "north", 0);
	add_exit(DDIR + "plaza.c", "west", 0);

	add_item(({"stream", "water", "river", "cliff", "cliff face"}), "@@stream");

	INSIDE
        DARK
}

stream()
{
	write(BS("The water comes mainly from the south cavern cliff face."
	 + " There is enough water flowing here for this to be properly"
	 + " called a river. The water is not flowing very fast but it is flowing"
	 + " down the street further west.", 70));
	return "";
}
